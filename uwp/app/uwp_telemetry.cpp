// Opt-in telemetry for the Xbox port (see uwp_telemetry.h, API in uwp/TELEMETRY_API.md).
//
// LocalState files: telemetry_id (the anonymous ID), telemetry ("on" / "off"; missing = not asked
// yet) and telemetry_session (written while a game runs, so the next start can tell that the run
// ended during the game: a crash, a hang the user closed, or the app closed from the Xbox Home menu).
// Everything is sent by one low-priority thread with libcurl; nothing is kept on disk for later.

#include "stdafx.h"
#include "uwp_telemetry.h"
#include "uwp_telemetry_scrub.h"
#include "winrt_min.h"
#include "rpcs3_version.h"

#include "Emu/System.h"
#include "Emu/Cell/timers.hpp"
#include "Emu/RSX/RSXThread.h"
#include "Emu/system_config.h"
#include "Emu/system_utils.hpp"
#include "Utilities/File.h"
#include "util/logs.hpp"
#include "util/sysinfo.hpp"

#include <bcrypt.h>
#include <curl/curl.h>
#include <zlib.h>

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <mutex>

LOG_CHANNEL(tel_log, "Telemetry");

namespace uwp_telemetry
{
	namespace
	{
#include "uwp_telemetry_roots.inc"

		constexpr std::string_view c_server = "https://rpcs3.emelinhabibovic.de";
		constexpr std::string_view c_app_version = RPCS3_XBOX_VERSION;
		// Logs bigger than this are sent as their start and end (the middle is cut out).
		constexpr u64 c_log_head = 16ull << 20, c_log_tail = 96ull << 20;
		constexpr usz c_max_events = 50;

		struct telemetry_cfg : cfg::node
		{
			cfg::_bool enabled{this, "Send logs to the developer", false};
		};

		telemetry_cfg g_cfg_tel;
		std::string g_local_dir;
		std::string g_install_id, g_session_id;
		atomic_t<consent> g_consent = consent::unknown;

		struct log_job
		{
			std::string path, kind, reason, title_id;
			bool sync = false;   // RPCS3.log of this run: flush the logger first
			bool fatal = false;  // the fatal error's log: drops the session marker once sent
			bool live = false;   // rpcs3_live: only the part of RPCS3.log written since the last part
			u32 attempts = 0;
		};

		std::mutex g_mutex;
		std::condition_variable g_cv;
		std::vector<std::string> g_events; // JSON objects, oldest first
		std::deque<log_job> g_logs;
		bool g_disabled_note = false; // send "telemetry_disabled" even though sending is off
		bool g_thread_started = false;

		// The running game (on_game_started .. on_game_stopped).
		bool g_in_game = false;
		bool g_fatal_sent = false;
		std::string g_game_id, g_game_title;
		std::chrono::steady_clock::time_point g_game_since;

		// Performance reports of the running game (on_perf): sent once a minute, at game exit and after
		// a fatal error, so one request carries ~6 "perf" events and their "stutter" events.
		std::vector<std::string> g_perf_pending;
		std::chrono::steady_clock::time_point g_perf_flushed;
		u64 g_run_frames = 0, g_run_stutters = 0;
		f64 g_run_secs = 0, g_run_min_fps = -1;
		constexpr u64 c_max_stutters = 300; // per game run

		// Live log: while a game runs, the part of RPCS3.log written since the last one goes up once a
		// minute; at game exit only the rest. Off for this app start once the server refuses parts (403).
		constexpr u64 c_live_max = 16ull << 20;
		u64 g_live_offset = 0; // upload thread only
		atomic_t<bool> g_live_off = false;
		std::chrono::steady_clock::time_point g_live_next;

		std::string session_file() { return g_local_dir + "telemetry_session"; }
		std::string log_dir() { return g_local_dir + "rpcs3/"; }

		std::string make_uuid()
		{
			u8 b[16]{};
			if (!BCRYPT_SUCCESS(BCryptGenRandom(nullptr, b, sizeof(b), BCRYPT_USE_SYSTEM_PREFERRED_RNG)))
				return {};
			b[6] = static_cast<u8>((b[6] & 0x0f) | 0x40); // version 4
			b[8] = static_cast<u8>((b[8] & 0x3f) | 0x80); // RFC 4122 variant
			return fmt::format("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
				b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);
		}

		bool valid_uuid(std::string_view s)
		{
			if (s.size() != 36)
				return false;
			for (usz i = 0; i < s.size(); i++)
			{
				const char c = s[i];
				if (i == 8 || i == 13 || i == 18 || i == 23 ? c != '-' : !((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')))
					return false;
			}
			return true;
		}

		bool valid_title_id(std::string_view s)
		{
			if (s.size() != 9)
				return false;
			for (usz i = 0; i < 9; i++)
				if (i < 4 ? !(s[i] >= 'A' && s[i] <= 'Z') : !(s[i] >= '0' && s[i] <= '9'))
					return false;
			return true;
		}

		std::string trim(std::string s)
		{
			while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' '))
				s.pop_back();
			return s;
		}

		// ---- JSON ----
		std::string json_str(std::string_view s, usz max = 1024)
		{
			std::string out = "\"";
			usz n = 0;
			for (usz i = 0; i < s.size() && n < max; i++, n++)
			{
				const u8 c = static_cast<u8>(s[i]);
				switch (c)
				{
				case '"': out += "\\\""; break;
				case '\\': out += "\\\\"; break;
				case '\n': out += "\\n"; break;
				case '\r': out += "\\r"; break;
				case '\t': out += "\\t"; break;
				default:
					if (c < 0x20)
						fmt::append(out, "\\u%04x", c);
					else
						out += static_cast<char>(c);
				}
			}
			// Don't end in the middle of a UTF-8 sequence.
			while (out.size() > 1 && (static_cast<u8>(out.back()) & 0xc0) == 0x80)
				out.pop_back();
			if (out.size() > 1 && static_cast<u8>(out.back()) >= 0xc0)
				out.pop_back();
			return out + "\"";
		}

		struct json_data
		{
			std::string body;
			json_data& add(std::string_view key, std::string_view value)
			{
				fmt::append(body, "%s%s:%s", body.empty() ? "" : ",", json_str(key), json_str(value));
				return *this;
			}
			// Without it a string literal would take the bool overload (a standard conversion).
			json_data& add(std::string_view key, const char* value)
			{
				return add(key, std::string_view(value));
			}
			json_data& add(std::string_view key, s64 value)
			{
				fmt::append(body, "%s%s:%d", body.empty() ? "" : ",", json_str(key), value);
				return *this;
			}
			json_data& add(std::string_view key, bool value)
			{
				fmt::append(body, "%s%s:%s", body.empty() ? "" : ",", json_str(key), value ? "true" : "false");
				return *this;
			}
			json_data& addf(std::string_view key, f64 value, int digits = 1)
			{
				if (!std::isfinite(value))
					value = 0;
				fmt::append(body, "%s%s:%.*f", body.empty() ? "" : ",", json_str(key), digits, value);
				return *this;
			}
		};

		std::string utc_now()
		{
			SYSTEMTIME t{};
			GetSystemTime(&t);
			return fmt::format("%04u-%02u-%02uT%02u:%02u:%02uZ", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
		}

		std::string make_event(std::string_view type, std::string_view title_id, std::string_view title, const json_data& data)
		{
			return fmt::format("{\"type\":%s,\"ts\":%s,\"title_id\":%s,\"title\":%s,\"data\":{%s}}", json_str(type), json_str(utc_now()),
				valid_title_id(title_id) ? json_str(title_id) : std::string("null"), title.empty() ? std::string("null") : json_str(title, 128), data.body);
		}

		void queue_event(std::string event)
		{
			{
				std::lock_guard lock(g_mutex);
				if (g_consent != consent::yes)
					return;
				// Keep the newest when the server is unreachable for a long time.
				if (g_events.size() >= 500)
					g_events.erase(g_events.begin());
				g_events.push_back(std::move(event));
			}
			g_cv.notify_one();
		}

		void queue_log(log_job job)
		{
			{
				std::lock_guard lock(g_mutex);
				if (g_consent != consent::yes)
					return;
				if (std::none_of(g_logs.begin(), g_logs.end(), [&](const log_job& j) { return j.path == job.path && j.reason == job.reason; }))
					g_logs.push_back(std::move(job));
			}
			g_cv.notify_one();
		}

		// ---- System info ----
		std::string from_hstring(HSTRING h)
		{
			UINT32 len = 0;
			const wchar_t* w = WindowsGetStringRawBuffer(h, &len);
			if (!w || !len)
				return {};
			std::string out(len * 3, '\0');
			out.resize(::WideCharToMultiByte(CP_UTF8, 0, w, static_cast<int>(len), out.data(), static_cast<int>(out.size()), nullptr, nullptr));
			return out;
		}

		// Windows.System.Profile.AnalyticsInfo (SDK metadata, IIDs from uwp/toolchain/gen_winrt_abi.py).
		struct IAnalyticsVersionInfo : IInspectable
		{
			virtual HRESULT STDMETHODCALLTYPE get_DeviceFamily(HSTRING* result) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DeviceFamilyVersion(HSTRING* result) = 0;
		};
		struct IAnalyticsInfoStatics : IInspectable
		{
			virtual HRESULT STDMETHODCALLTYPE get_VersionInfo(IAnalyticsVersionInfo** result) = 0;
			virtual HRESULT STDMETHODCALLTYPE get_DeviceForm(HSTRING* result) = 0;
		};
		constexpr GUID IID_IAnalyticsInfoStatics = {0x1d5ee066, 0x188d, 0x5ba9, {0x43, 0x87, 0xac, 0xae, 0xb0, 0xe7, 0xe3, 0x05}};

		struct device_info
		{
			std::string form;    // "Xbox Series X", "Xbox Series S", "Xbox One X", ...
			std::string family;  // "Windows.Xbox"
			std::string os;      // 10.0.26100.xxxx
		};

		const device_info& get_device_info()
		{
			static const device_info info = []()
			{
				device_info d;
				IAnalyticsInfoStatics* statics = nullptr;
				if (FAILED(winrt_min::get_factory(L"Windows.System.Profile.AnalyticsInfo", IID_IAnalyticsInfoStatics, &statics)) || !statics)
					return d;
				HSTRING h = nullptr;
				if (SUCCEEDED(statics->get_DeviceForm(&h)) && h)
				{
					d.form = from_hstring(h);
					WindowsDeleteString(h);
				}
				IAnalyticsVersionInfo* version = nullptr;
				if (SUCCEEDED(statics->get_VersionInfo(&version)) && version)
				{
					if (SUCCEEDED(version->get_DeviceFamily(&h)) && h)
					{
						d.family = from_hstring(h);
						WindowsDeleteString(h);
					}
					if (SUCCEEDED(version->get_DeviceFamilyVersion(&h)) && h)
					{
						// A 64-bit number holding the four 16-bit parts of the version.
						const u64 v = std::strtoull(from_hstring(h).c_str(), nullptr, 10);
						WindowsDeleteString(h);
						d.os = fmt::format("%u.%u.%u.%u", v >> 48, (v >> 32) & 0xffff, (v >> 16) & 0xffff, v & 0xffff);
					}
					version->Release();
				}
				statics->Release();
				return d;
			}();
			return info;
		}

		// Which build sent it: the package version, the git commit it was built from and RPCS3's version.
		json_data& add_release(json_data& d)
		{
			const auto [commit, hash] = rpcs3::get_commit_and_hash();
			d.add("app_version", c_app_version);
			d.add("build_commit", hash);
			d.add("build_branch", rpcs3::get_branch());
			d.add("rpcs3_version", rpcs3::get_version_and_branch());
			return d;
		}

		json_data system_data()
		{
			const device_info& dev = get_device_info();
			json_data d;
			add_release(d);
			d.add("device", dev.form.empty() ? std::string("unknown") : dev.form);
			d.add("device_family", dev.family);
			d.add("os_version", dev.os);
			d.add("firmware", utils::get_firmware_version());
			d.add("cpu", utils::get_cpu_brand());
			MEMORYSTATUSEX mem{sizeof(mem)};
			if (GlobalMemoryStatusEx(&mem))
				d.add("free_ram_mb", static_cast<s64>(mem.ullAvailPhys >> 20)).add("total_ram_mb", static_cast<s64>(mem.ullTotalPhys >> 20));
			return d;
		}

		// ---- Logs: scrub, then gzip ----
		scrubber make_scrubber()
		{
			scrubber sc;
			// The RPCN account (rpcn.yml): name, password hash, token.
			if (const fs::file f{fs::get_config_dir(true) + "rpcn.yml"})
			{
				for (const std::string& line : fmt::split(f.to_string(), {"\n"}))
				{
					const std::string_view l = line;
					for (const auto& [key, label] : {std::pair<std::string_view, std::string_view>{"NPID: ", "rpcn_user"}, {"Password: ", "rpcn_password"}, {"Token: ", "rpcn_token"}})
					{
						if (l.substr(0, key.size()) == key)
						{
							std::string value = trim(std::string(l.substr(key.size())));
							if (value.size() >= 2 && (value.front() == '"' || value.front() == '\'') && value.back() == value.front())
								value = value.substr(1, value.size() - 2);
							if (!value.empty())
								sc.known_strings.push_back({std::move(value), std::string(label)});
						}
					}
				}
			}
			// The PS3 user names of the XMB (dev_hdd0/home/<id>/localusername).
			const std::string home = rpcs3::utils::get_hdd0_dir() + "home/";
			for (const auto& entry : fs::dir(home))
			{
				if (!entry.is_directory || entry.name == "." || entry.name == "..")
					continue;
				if (const fs::file f{home + entry.name + "/localusername"})
				{
					std::string name = trim(f.to_string());
					if (!name.empty() && name != "User")
						sc.known_strings.push_back({std::move(name), "ps3_user"});
				}
			}
			return sc;
		}

		struct gzip_writer
		{
			z_stream z{};
			std::string out;
			bool ok = false;

			gzip_writer() { ok = deflateInit2(&z, 6, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY) == Z_OK; }
			~gzip_writer() { deflateEnd(&z); }

			void write(std::string_view data, bool finish = false)
			{
				z.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));
				z.avail_in = static_cast<uInt>(data.size());
				int res = Z_OK;
				do
				{
					const usz pos = out.size();
					out.resize(pos + 256 * 1024);
					z.next_out = reinterpret_cast<Bytef*>(out.data() + pos);
					z.avail_out = 256 * 1024;
					res = deflate(&z, finish ? Z_FINISH : Z_NO_FLUSH);
					out.resize(out.size() - z.avail_out);
				}
				while (res == Z_OK && (z.avail_in || (finish && res != Z_STREAM_END)));
			}
		};

		// The log, line by line through the scrubber, gzip-compressed. False when it can't be read.
		bool build_log(const std::string& path, std::string& gz)
		{
			fs::file f(path);
			if (!f)
				return false;
			const scrubber sc = make_scrubber();
			gzip_writer gw;
			if (!gw.ok)
				return false;

			const u64 size = f.size();
			const bool cut = size > c_log_head + c_log_tail;
			std::string buf(4 << 20, '\0'), lines, pending;
			u64 read = 0;
			bool skipped = false;
			const auto feed = [&](std::string_view chunk)
			{
				lines.clear();
				usz start = 0;
				for (usz nl = chunk.find('\n'); nl != umax; start = nl + 1, nl = chunk.find('\n', start))
				{
					pending.append(chunk.substr(start, nl - start));
					lines += sc.scrub(pending);
					lines += '\n';
					pending.clear();
				}
				pending.append(chunk.substr(start));
				gw.write(lines);
			};
			while (true)
			{
				if (cut && !skipped && read >= c_log_head)
				{
					// The middle is cut out; continue at the start of a line.
					pending.clear();
					f.seek(size - c_log_tail);
					read = size - c_log_tail;
					std::string rest(64 * 1024, '\0');
					const usz n = f.read(rest.data(), rest.size());
					const usz nl = std::string_view(rest.data(), n).find('\n');
					lines.clear();
					fmt::append(lines, "\n[Telemetry: %u MB of the log were left out here]\n", (size - c_log_head - c_log_tail) >> 20);
					gw.write(lines);
					lines.clear();
					f.seek(read + (nl == umax ? n : nl + 1));
					read += nl == umax ? n : nl + 1;
					skipped = true;
				}
				const u64 want = cut && !skipped ? std::min<u64>(buf.size(), c_log_head - read) : buf.size();
				const usz n = f.read(buf.data(), want);
				if (!n)
					break;
				read += n;
				feed(std::string_view(buf.data(), n));
			}
			if (!pending.empty())
			{
				lines = sc.scrub(pending);
				gw.write(lines);
			}
			gw.write({}, true);
			gz = std::move(gw.out);
			return true;
		}

		// ---- HTTP ----
		usz curl_discard(char*, usz size, usz n, void*)
		{
			return size * n;
		}

		usz curl_header(char* data, usz size, usz n, void* user)
		{
			const std::string_view h(data, size * n);
			if (h.size() > 12 && (h.substr(0, 12) == "Retry-After:" || h.substr(0, 12) == "retry-after:"))
				*static_cast<u32*>(user) = static_cast<u32>(std::strtoul(std::string(h.substr(12)).c_str(), nullptr, 10));
			return size * n;
		}

		// POSTs to the server; returns the HTTP status, or 0 when there was no answer.
		long post(std::string_view path, std::string_view content_type, const std::vector<std::string>& headers, const std::string& body, u32& retry_after)
		{
			CURL* c = curl_easy_init();
			if (!c)
				return 0;
			const std::string url = fmt::format("%s%s", c_server, path);
			const std::string agent = fmt::format("RPCS3Xbox/%s", c_app_version);
			curl_slist* list = nullptr;
			list = curl_slist_append(list, fmt::format("Content-Type: %s", content_type).c_str());
			list = curl_slist_append(list, fmt::format("X-Telemetry-Install: %s", g_install_id).c_str());
			list = curl_slist_append(list, fmt::format("X-Telemetry-Session: %s", g_session_id).c_str());
			list = curl_slist_append(list, fmt::format("X-Telemetry-App-Version: %s", c_app_version).c_str());
			list = curl_slist_append(list, "Expect:");
			for (const std::string& h : headers)
				list = curl_slist_append(list, h.c_str());

			curl_blob roots{const_cast<char*>(s_telemetry_roots), sizeof(s_telemetry_roots) - 1, CURL_BLOB_NOCOPY};
			char error[CURL_ERROR_SIZE]{};
			curl_easy_setopt(c, CURLOPT_URL, url.c_str());
			curl_easy_setopt(c, CURLOPT_USERAGENT, agent.c_str());
			curl_easy_setopt(c, CURLOPT_HTTPHEADER, list);
			curl_easy_setopt(c, CURLOPT_POST, 1L);
			curl_easy_setopt(c, CURLOPT_POSTFIELDS, body.data());
			curl_easy_setopt(c, CURLOPT_POSTFIELDSIZE_LARGE, static_cast<curl_off_t>(body.size()));
			curl_easy_setopt(c, CURLOPT_CAINFO_BLOB, &roots);
			curl_easy_setopt(c, CURLOPT_NOSIGNAL, 1L);
			curl_easy_setopt(c, CURLOPT_CONNECTTIMEOUT, 20L);
			curl_easy_setopt(c, CURLOPT_TIMEOUT, 600L);
			curl_easy_setopt(c, CURLOPT_ERRORBUFFER, error);
			curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, curl_discard);
			curl_easy_setopt(c, CURLOPT_HEADERFUNCTION, curl_header);
			curl_easy_setopt(c, CURLOPT_HEADERDATA, &retry_after);
			const CURLcode res = curl_easy_perform(c);
			long status = 0;
			if (res == CURLE_OK)
				curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &status);
			else
				tel_log.warning("Upload to %s failed: %s (%s)", path, curl_easy_strerror(res), error);
			curl_slist_free_all(list);
			curl_easy_cleanup(c);
			return status;
		}

		enum class sent
		{
			ok,
			drop,  // the server refused it (4xx): don't send again
			retry, // no answer, 429 or 5xx
		};

		sent result_of(long status)
		{
			if (status >= 200 && status < 300)
				return sent::ok;
			if (status == 0 || status == 429 || status >= 500)
				return sent::retry;
			return sent::drop;
		}

		sent send_events(const std::vector<std::string>& events, u32& retry_after)
		{
			std::string body = "{\"events\":[";
			for (usz i = 0; i < events.size(); i++)
				fmt::append(body, "%s%s", i ? "," : "", events[i]);
			body += "]}";
			const long status = post("/api/v1/events", "application/json", {}, body, retry_after);
			if (status && status != 200)
				tel_log.warning("The server answered %d to %u events", status, events.size());
			return result_of(status);
		}

		sent send_log(const log_job& job, u32& retry_after);

		// The new part of RPCS3.log (whole lines, at most c_live_max, newest kept), scrubbed and gzipped.
		sent send_live(const log_job& job, u32& retry_after)
		{
			logs::listener::sync_all();
			fs::file f(job.path);
			if (!f)
				return sent::drop;
			const u64 size = f.size();
			if (size < g_live_offset)
				g_live_offset = 0; // a new file
			u64 start = g_live_offset;
			if (size - start > c_live_max)
				start = size - c_live_max;
			std::string data(size - start, '\0');
			f.seek(start);
			data.resize(f.read(data.data(), data.size()));
			if (start != g_live_offset)
			{
				// Cut: continue at the start of a line.
				const usz nl = data.find('\n');
				const usz cut = nl == umax ? data.size() : nl + 1;
				data.erase(0, cut);
				start += cut;
			}
			const usz last = data.rfind('\n');
			data.resize(last == umax ? 0 : last + 1);
			if (data.empty())
				return sent::ok;
			const u64 end = start + data.size();

			const scrubber sc = make_scrubber();
			std::string lines;
			lines.reserve(data.size());
			for (usz pos = 0; pos < data.size();)
			{
				const usz nl = data.find('\n', pos);
				lines += sc.scrub(std::string_view(data).substr(pos, nl - pos));
				lines += '\n';
				pos = nl + 1;
			}
			gzip_writer gw;
			if (!gw.ok)
				return sent::drop;
			gw.write(lines, true);

			std::vector<std::string> headers{"X-Telemetry-Log-Kind: rpcs3_live", "X-Telemetry-Reason: " + job.reason,
				fmt::format("X-Telemetry-Log-Offset: %u", start), fmt::format("X-Telemetry-Log-End: %u", end)};
			if (valid_title_id(job.title_id))
				headers.push_back("X-Telemetry-Title-Id: " + job.title_id);
			const long status = post("/api/v1/logs", "application/gzip", headers, gw.out, retry_after);
			if (status == 200)
			{
				g_live_offset = end;
				return sent::ok;
			}
			if (status == 403)
			{
				// Turned off on the server: no more parts this app start; at exit the whole log, as before.
				tel_log.notice("The server doesn't take live logs");
				g_live_off = true;
				if (job.reason == "periodic")
					return sent::drop;
				log_job full = job;
				full.live = false;
				full.kind = "rpcs3";
				return send_log(full, retry_after);
			}
			if (status)
				tel_log.warning("The server answered %d to the live log", status);
			return result_of(status);
		}

		sent send_log(const log_job& job, u32& retry_after)
		{
			if (job.live)
				return send_live(job, retry_after);
			if (job.sync)
				logs::listener::sync_all();
			std::string gz;
			if (!build_log(job.path, gz))
				return sent::drop;
			std::vector<std::string> headers{"X-Telemetry-Log-Kind: " + job.kind};
			if (!job.reason.empty())
				headers.push_back("X-Telemetry-Reason: " + job.reason);
			if (valid_title_id(job.title_id))
				headers.push_back("X-Telemetry-Title-Id: " + job.title_id);
			const long status = post("/api/v1/logs", "application/gzip", headers, gz, retry_after);
			if (status == 200)
				tel_log.notice("Sent %s (%u KB compressed)", job.kind, gz.size() >> 10);
			else if (status)
				tel_log.warning("The server answered %d to the %s log", status, job.kind);
			return result_of(status);
		}

		DWORD WINAPI upload_thread(void*)
		{
			RoInitialize(RO_INIT_MULTITHREADED);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
			u32 failures = 0;
			while (true)
			{
				std::vector<std::string> events;
				std::optional<log_job> job;
				bool disabled_note = false;
				{
					std::unique_lock lock(g_mutex);
					const auto ready = [] { return g_disabled_note || (g_consent == consent::yes && (!g_events.empty() || !g_logs.empty())); };
					const auto live = [] { return g_in_game && g_consent == consent::yes && !g_live_off; };
					while (!ready())
					{
						if (!live())
						{
							g_cv.wait(lock, [&] { return ready() || live(); });
							continue;
						}
						if (g_cv.wait_until(lock, g_live_next, ready))
							break;
						if (live() && std::chrono::steady_clock::now() >= g_live_next)
						{
							g_live_next = std::chrono::steady_clock::now() + std::chrono::seconds(60);
							if (std::none_of(g_logs.begin(), g_logs.end(), [](const log_job& j) { return j.live; }))
								g_logs.push_back({log_dir() + "RPCS3.log", "rpcs3_live", "periodic", g_game_id, true, false, true});
						}
					}
					if (g_disabled_note)
					{
						disabled_note = true;
						g_disabled_note = false;
					}
					else if (!g_events.empty())
					{
						const usz n = std::min(g_events.size(), c_max_events);
						events.assign(std::make_move_iterator(g_events.begin()), std::make_move_iterator(g_events.begin() + n));
						g_events.erase(g_events.begin(), g_events.begin() + n);
					}
					else
					{
						job = std::move(g_logs.front());
						g_logs.pop_front();
					}
				}

				u32 retry_after = 0;
				sent res = sent::ok;
				if (disabled_note)
				{
					// Best effort, once.
					post("/api/v1/events", "application/json", {}, fmt::format("{\"events\":[%s]}", make_event("telemetry_disabled", {}, {}, {})), retry_after);
					continue;
				}
				if (!events.empty())
				{
					res = send_events(events, retry_after);
					if (res == sent::retry)
					{
						std::lock_guard lock(g_mutex);
						g_events.insert(g_events.begin(), std::make_move_iterator(events.begin()), std::make_move_iterator(events.end()));
					}
				}
				else if (job)
				{
					res = send_log(*job, retry_after);
					if (res == sent::ok && job->fatal)
						fs::remove_file(session_file());
					if (res == sent::retry && ++job->attempts < 5)
					{
						std::lock_guard lock(g_mutex);
						g_logs.push_front(std::move(*job));
					}
				}

				if (res != sent::retry)
				{
					failures = 0;
					continue;
				}
				// The server or network is down: 30 s, 1, 2, 4 ... up to 30 min, or what Retry-After says.
				failures++;
				const u32 wait = retry_after ? std::min<u32>(retry_after, 3600) : std::min<u32>(30u << std::min<u32>(failures - 1, 6), 1800);
				std::unique_lock lock(g_mutex);
				g_cv.wait_for(lock, std::chrono::seconds(wait), [] { return g_disabled_note; });
			}
		}

		void start_thread()
		{
			std::lock_guard lock(g_mutex);
			if (g_thread_started)
				return;
			g_thread_started = true;
			CloseHandle(CreateThread(nullptr, 2 * 1024 * 1024, upload_thread, nullptr, 0, nullptr));
		}

		// ---- Performance reports ----
		u64 app_memory_mb(u64* limit_mb)
		{
			static winrt_min::IMemoryManagerStatics* const mm = []
			{
				winrt_min::IMemoryManagerStatics* p = nullptr;
				return SUCCEEDED(winrt_min::get_factory(L"Windows.System.MemoryManager", winrt_min::IID_IMemoryManagerStatics, &p)) ? p : nullptr;
			}();
			UINT64 usage = 0, limit = 0;
			if (mm)
			{
				mm->get_AppMemoryUsage(&usage);
				mm->get_AppMemoryUsageLimit(&limit);
			}
			*limit_mb = limit >> 20;
			return usage >> 20;
		}

		// Moves the pending perf events to the upload queue (caller holds g_mutex).
		void flush_perf_locked()
		{
			g_perf_flushed = std::chrono::steady_clock::now();
			if (g_perf_pending.empty() || g_consent != consent::yes)
			{
				g_perf_pending.clear();
				return;
			}
			for (std::string& e : g_perf_pending)
			{
				if (g_events.size() >= 500)
					g_events.erase(g_events.begin());
				g_events.push_back(std::move(e));
			}
			g_perf_pending.clear();
			g_cv.notify_one();
		}

		// RSX thread, every 10 s while a game runs (RSXThread.cpp flip). Raw numbers only: the server
		// decides what limited the frame rate, so its rules can change without a new build.
		void on_perf(const rsx::uwp_perf_window& w)
		{
			if (g_consent != consent::yes)
				return;
			const auto now = std::chrono::steady_clock::now();
			const f64 now_sys = get_system_time() / 1e6;
			std::string title_id, title;
			f64 t_s = 0;
			{
				std::lock_guard lock(g_mutex);
				if (!g_in_game)
					return;
				title_id = g_game_id, title = g_game_title;
				t_s = std::chrono::duration<f64>(now - g_game_since).count();
			}

			u64 mem_limit = 0;
			const u64 mem = app_memory_mb(&mem_limit);
			f64 ppu_total = 0, spu_total = 0;
			for (const auto& [name, pct] : w.ppu)
				ppu_total += pct;
			for (f64 pct : w.spu)
				spu_total += pct;
			const auto ppu_name = [&](usz i) { return i < w.ppu.size() ? w.ppu[i].first : std::string(); };
			const auto ppu_pct = [&](usz i) { return i < w.ppu.size() ? w.ppu[i].second : 0.; };

			json_data d;
			d.add("t_s", static_cast<s64>(t_s));
			d.addf("secs", w.secs);
			d.addf("fps", w.fps);
			d.add("frames", static_cast<s64>(w.frames));
			d.addf("frame_max_ms", w.frame_max_ms, 0);
			d.add("frames_50ms", static_cast<s64>(w.frames_50ms));
			d.add("frames_100ms", static_cast<s64>(w.frames_100ms));
			d.add("stutters", static_cast<s64>(w.stutters.size()));
			d.addf("rsx_busy", w.rsx_busy, 0);
			d.addf("rsx_idle", w.rsx_idle, 0);
			d.addf("gpu_wait_ms", w.gpu_wait_ms, 2);
			d.addf("submit_ms", w.submit_ms, 2);
			d.addf("present_ms", w.present_wait_ms, 2);
			d.addf("draws", w.draws, 0);
			d.addf("submits", w.submits);
			d.addf("setup_ms", w.setup_ms, 2);
			d.addf("vertex_ms", w.vertex_ms, 2);
			d.addf("texture_ms", w.texture_ms, 2);
			d.addf("draw_ms", w.draw_ms, 2);
			d.add("shaders", static_cast<s64>(w.new_pipelines));
			d.add("ppu1", ppu_name(0));
			d.addf("ppu1_pct", ppu_pct(0), 0);
			d.add("ppu2", ppu_name(1));
			d.addf("ppu2_pct", ppu_pct(1), 0);
			d.addf("ppu_total", ppu_total, 0);
			d.add("ppu_threads", static_cast<s64>(w.ppu.size()));
			d.addf("spu_max", w.spu.empty() ? 0. : w.spu[0], 0);
			d.addf("spu_total", spu_total, 0);
			d.add("spu_threads", static_cast<s64>(w.spu.size()));
			d.add("mem_mb", static_cast<s64>(mem));
			d.add("mem_limit_mb", static_cast<s64>(mem_limit));

			std::vector<std::string> events{make_event("perf", title_id, title, d)};
			for (const rsx::uwp_perf_stutter& st : w.stutters)
			{
				json_data s;
				s.add("t_s", static_cast<s64>(std::max(0., t_s - (now_sys - st.at_s))));
				s.addf("frame_ms", st.frame_ms, 0);
				s.addf("avg_ms", st.avg_ms);
				s.add("shaders", static_cast<s64>(st.new_pipelines));
				s.addf("submit_ms", st.submit_ms);
				s.addf("present_ms", st.present_wait_ms);
				s.addf("present_copy_ms", st.present_copy_ms);
				s.addf("rsx_idle_ms", st.rsx_idle_ms);
				s.addf("gpu_wait_ms", st.gpu_wait_ms);
				s.addf("setup_ms", st.setup_ms);
				s.addf("vertex_ms", st.vertex_ms);
				s.addf("texture_ms", st.texture_ms);
				s.addf("draw_ms", st.draw_ms);
				s.add("draws", static_cast<s64>(st.draws));
				s.add("submits", static_cast<s64>(st.submits));
				s.addf("mem_poll_ago_ms", st.mem_poll_ago_ms, 0);
				s.add("rsx_phases", st.rsx_phases);
				// What the game threads did in the same 10 s.
				s.add("ppu1", ppu_name(0));
				s.addf("ppu1_pct", ppu_pct(0), 0);
				s.addf("spu_max", w.spu.empty() ? 0. : w.spu[0], 0);
				s.addf("window_fps", w.fps);
				s.add("mem_mb", static_cast<s64>(mem));
				events.push_back(make_event("stutter", title_id, title, s));
			}

			std::lock_guard lock(g_mutex);
			if (!g_in_game)
				return;
			g_run_frames += w.frames;
			g_run_secs += w.secs;
			g_run_min_fps = g_run_min_fps < 0 ? w.fps : std::min(g_run_min_fps, w.fps);
			for (usz i = 0; i < events.size(); i++)
			{
				if (i && g_run_stutters >= c_max_stutters)
					break;
				g_run_stutters += i != 0;
				g_perf_pending.push_back(std::move(events[i]));
			}
			if (now - g_perf_flushed >= std::chrono::seconds(60) || g_perf_pending.size() >= 40)
				flush_perf_locked();
		}

		// What the previous run left: telemetry_session means it ended while a game ran.
		void report_previous_run()
		{
			const fs::file f{session_file()};
			if (!f)
				return;
			const std::vector<std::string> lines = fmt::split(f.to_string(), {"\n"}, false);
			const std::string title_id = !lines.empty() ? lines[0] : std::string();
			const std::string title = lines.size() > 1 ? lines[1] : std::string();
			const std::string kind = lines.size() > 2 ? lines[2] : std::string();
			const bool fatal = lines.size() > 3 && lines[3] == "fatal";
			// Suspended (Xbox Home) and never resumed, or a run of another version (an update was
			// installed over the running app; markers before 0.1.34.76 have no version): ended from outside.
			const bool suspended = std::find(lines.begin(), lines.end(), "suspended") != lines.end();
			const auto version = std::find_if(lines.begin(), lines.end(), [](const std::string& l) { return l.starts_with("v="); });
			const bool updated = version == lines.end() || version->substr(2) != c_app_version;
			fs::remove_file(session_file());
			tel_log.notice("The previous run ended during '%s' (%s): fatal %d, suspended %d, updated %d", title, kind, fatal, suspended, updated);

			if (!fatal && (suspended || updated))
			{
				json_data d;
				d.add("kind", kind);
				d.add("reason", suspended ? "app_closed" : "app_updated");
				d.add("note", suspended ? "The app was closed while suspended (Xbox Home), with this running." :
					"The app was updated or reinstalled while this ran.");
				queue_event(make_event("game_exit", title_id, title, d));
				queue_log({log_dir() + "RPCS3.prev.log", "rpcs3_prev", "game_exit", title_id});
				return;
			}

			json_data d;
			d.add("reason", fatal ? "fatal_error" : "ended_during_game");
			d.add("kind", kind);
			d.add("note", fatal ? "Fatal emulator error; its log wasn't sent in that run." : "The app ended while this ran: a crash, a hang, or closed from the Xbox Home menu.");
			queue_event(make_event("crash", title_id, title, d));
			queue_log({log_dir() + "RPCS3.prev.log", "rpcs3_prev", "crash", title_id});
			queue_log({g_local_dir + "mesa.prev.log", "mesa", "crash", title_id});
			queue_log({g_local_dir + "memory.prev.log", "memory", "crash", title_id});
			// The heap guard's fail-fast leaves no line in RPCS3.log: a corrupted block or a failed new.
			if (fs::stat_t st{}; fs::get_stat(g_local_dir + "heap_guard.prev.log", st) && st.size)
				queue_log({g_local_dir + "heap_guard.prev.log", "crash", "crash", title_id});
		}

		void queue_app_start()
		{
			queue_event(make_event("app_start", {}, {}, system_data()));
		}
	}

	void init(const std::string& local_dir)
	{
		g_local_dir = local_dir;
		g_session_id = make_uuid();

		const std::string id_file = local_dir + "telemetry_id";
		if (const fs::file f{id_file})
			g_install_id = trim(f.to_string());
		if (!valid_uuid(g_install_id))
		{
			g_install_id = make_uuid();
			fs::write_file(id_file, fs::rewrite, g_install_id);
		}

		const std::string state = fs::file{local_dir + "telemetry"} ? trim(fs::file{local_dir + "telemetry"}.to_string()) : std::string();
		g_consent = state == "on" ? consent::yes : state == "off" ? consent::no : consent::unknown;
		g_cfg_tel.enabled.from_string(g_consent == consent::yes ? "true" : "false");
		rsx::g_uwp_perf_sink = on_perf;
		tel_log.notice("Anonymous ID %s, sending %s", g_install_id, g_consent == consent::yes ? "on" : g_consent == consent::no ? "off" : "not asked yet");

		if (g_consent == consent::yes)
		{
			start_thread();
			report_previous_run();
			queue_app_start();
		}
		else
		{
			// Not sent, but not reported later either.
			fs::remove_file(session_file());
		}
	}

	std::string_view tls_roots()
	{
		return {s_telemetry_roots, sizeof(s_telemetry_roots) - 1};
	}

	const std::string& install_id()
	{
		return g_install_id;
	}

	consent get_consent()
	{
		return g_consent;
	}

	void set_consent(bool yes)
	{
		const consent before = g_consent;
		fs::write_file(g_local_dir + "telemetry", fs::rewrite, std::string(yes ? "on" : "off"));
		g_cfg_tel.enabled.from_string(yes ? "true" : "false");
		tel_log.notice("Sending logs to the developer turned %s", yes ? "on" : "off");
		if (yes)
		{
			if (before == consent::yes)
				return;
			g_consent = consent::yes;
			start_thread();
			// The first yes of this install counts it (the server counts installs by their first event).
			const std::string marker = g_local_dir + "telemetry_installed";
			if (!fs::is_file(marker))
			{
				queue_event(make_event("install", {}, {}, system_data()));
				fs::write_file(marker, fs::rewrite, utc_now());
			}
			queue_app_start();
			// This run's log so far (system, settings, storage): each install's setup is on record from the start.
			queue_log({log_dir() + "RPCS3.log", "rpcs3", "app_start", {}, true});
			if (g_in_game)
			{
				std::lock_guard lock(g_mutex);
				fs::write_file(session_file(), fs::rewrite, fmt::format("%s\n%s\n%s\nv=%s\n", g_game_id, g_game_title, "game", c_app_version));
			}
			return;
		}

		g_consent = consent::no;
		fs::remove_file(session_file());
		{
			std::lock_guard lock(g_mutex);
			g_events.clear();
			g_logs.clear();
			g_perf_pending.clear();
			g_disabled_note = before == consent::yes && g_thread_started;
		}
		g_cv.notify_one();
	}

	cfg::_bool& setting()
	{
		return g_cfg_tel.enabled;
	}

	void on_game_started()
	{
		std::string title_id = Emu.GetTitleID(), title = Emu.GetTitle();
		const bool vsh = Emu.IsVsh();
		const std::string kind = vsh ? "xmb" : valid_title_id(title_id) ? "game" : "homebrew";
		if (vsh)
		{
			title_id.clear();
			title = "XMB";
		}
		{
			std::lock_guard lock(g_mutex);
			if (g_in_game)
				return; // resumed, not started
			g_in_game = true;
			g_fatal_sent = false;
			g_game_id = title_id;
			g_game_title = title;
			g_game_since = std::chrono::steady_clock::now();
			g_perf_pending.clear();
			g_perf_flushed = g_game_since;
			g_live_next = g_game_since + std::chrono::seconds(60);
			g_run_frames = g_run_stutters = 0;
			g_run_secs = 0, g_run_min_fps = -1;
		}
		g_cv.notify_one(); // starts the live log minute
		if (g_consent != consent::yes)
			return;

		fs::write_file(session_file(), fs::rewrite, fmt::format("%s\n%s\n%s\nv=%s\n", title_id, title, kind, c_app_version));
		json_data d;
		d.add("kind", kind);
		add_release(d);
		d.add("game_version", Emu.GetAppVersion());
		d.add("renderer", g_cfg.video.renderer.to_string());
		d.add("ppu_decoder", g_cfg.core.ppu_decoder.to_string());
		d.add("spu_decoder", g_cfg.core.spu_decoder.to_string());
		d.add("resolution_scale", static_cast<s64>(g_cfg.video.resolution_scale_percent.get()));
		d.add("frame_limit", g_cfg.video.frame_limit.to_string());
		d.add("shader_mode", g_cfg.video.shadermode.to_string());
		d.add("vblank_rate", static_cast<s64>(g_cfg.video.vblank_rate.get()));
		d.add("firmware", utils::get_firmware_version());
		d.add("device", get_device_info().form);
		queue_event(make_event("game_launch", title_id, title, d));
	}

	void on_game_stopped()
	{
		std::string title_id, title;
		s64 secs = 0;
		bool fatal = false;
		u64 frames = 0, stutters = 0;
		f64 perf_secs = 0, min_fps = -1;
		{
			std::lock_guard lock(g_mutex);
			if (!g_in_game)
				return;
			flush_perf_locked();
			g_in_game = false;
			frames = g_run_frames, stutters = g_run_stutters, perf_secs = g_run_secs, min_fps = g_run_min_fps;
			title_id = g_game_id;
			title = g_game_title;
			fatal = g_fatal_sent;
			secs = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - g_game_since).count();
		}
		if (g_consent != consent::yes)
			return;
		if (!fatal)
			fs::remove_file(session_file());

		json_data d;
		d.add("duration_s", secs);
		if (perf_secs > 0)
		{
			d.addf("avg_fps", frames / perf_secs);
			d.addf("min_fps", min_fps);
			d.add("stutters", static_cast<s64>(stutters));
		}
		queue_event(make_event("game_exit", title_id, title, d));
		if (!fatal)
			queue_log({log_dir() + "RPCS3.log", g_live_off ? "rpcs3" : "rpcs3_live", "game_exit", title_id, true, false, !g_live_off});
	}

	void on_suspend()
	{
		{
			std::lock_guard lock(g_mutex);
			const bool marker = fs::is_file(session_file());
			if (g_in_game && g_consent == consent::yes && marker)
			{
				const bool ok = fs::write_file<true>(session_file(), fs::write + fs::append, std::string_view{"suspended\n"});
				tel_log.notice("Suspended: session %s", ok ? "marked" : fmt::format("not marked (%s)", fs::g_tls_error));
			}
			else
			{
				tel_log.notice("Suspended: session not marked (in game %d, consent %d, marker %d)", g_in_game, g_consent == consent::yes, marker);
			}
		}
		// The app can be closed while suspended without running again: get these lines to disk now.
		logs::listener::sync_all();
	}

	void on_resume()
	{
		std::lock_guard lock(g_mutex);
		const fs::file f{session_file()};
		if (!f)
			return;
		std::string text = f.to_string();
		if (const usz pos = text.find("suspended\n"); pos != umax)
		{
			text.erase(pos);
			fs::write_file(session_file(), fs::rewrite, text);
			tel_log.notice("Resumed: suspend mark removed");
		}
	}

	void on_fatal(std::string_view text)
	{
		std::string title_id, title;
		{
			std::lock_guard lock(g_mutex);
			if (g_fatal_sent || g_consent != consent::yes)
				return;
			g_fatal_sent = true;
			flush_perf_locked();
			title_id = g_game_id;
			title = g_in_game ? g_game_title : std::string();
		}
		// Marked, so a log that couldn't be sent before the app ended is sent on the next start.
		if (g_in_game)
			fs::write_file(session_file(), fs::rewrite, fmt::format("%s\n%s\n%s\nfatal\nv=%s\n", title_id, title, "game", c_app_version));
		const scrubber sc = make_scrubber();
		json_data d;
		d.add("reason", "fatal_error");
		d.add("message", sc.scrub(text));
		queue_event(make_event("crash", title_id, title, d));
		queue_log({log_dir() + "RPCS3.log", g_live_off ? "rpcs3" : "rpcs3_live", "crash", title_id, true, true, !g_live_off});
		// This run's Dozen and memory logs too (sent only after silent ends so far): Dozen writes why a call
		// failed there, e.g. "ID3D12GraphicsCommandList::Close failed: 0x..." with the D3D12 messages behind
		// the LittleBigPlanet VK_ERROR_OUT_OF_HOST_MEMORY at 2.8 GB of 5 on .77.
		queue_log({g_local_dir + "mesa.log", "mesa", "crash", title_id});
		queue_log({g_local_dir + "memory.log", "memory", "crash", title_id});
	}

	std::string consent_title()
	{
		return "Help improve RPCS3 for Xbox?";
	}

	std::string consent_text()
	{
		return fmt::format(
			"Most problems of this port only show up on consoles I don't have. If you agree, the app sends its emulator log to "
			"rpcs3.emelinhabibovic.de every minute while a game or the XMB runs and after a crash, so I can see which games run, "
			"how fast, and why they fail.\n\n"
			"Sent: the emulator log, frame rate numbers, the app version, the console model, the game's title ID and name, and an anonymous ID "
			"made at random on this console (%s, also shown at the top of the menu).\n\n"
			"Never sent: your gamertag or Microsoft account, RPCN username, password, token or email, other players' names, "
			"IP addresses, your location or the list of games you have. They are removed from the logs before upload.\n\n"
			"You can turn this off at any time in Settings > Send logs to the developer.",
			g_install_id);
	}
}
