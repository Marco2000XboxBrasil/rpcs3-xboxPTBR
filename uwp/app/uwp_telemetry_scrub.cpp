// Personal data filter for telemetry log uploads (see uwp_telemetry_scrub.h). Hand-written scanners
// instead of std::regex: a log can be 100+ MB and is filtered on the console.

#include "uwp_telemetry_scrub.h"

#include <cstddef>

namespace uwp_telemetry
{
	namespace
	{
		bool is_digit(char c) { return c >= '0' && c <= '9'; }
		bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
		bool is_alnum(char c) { return is_digit(c) || is_alpha(c); }
		bool is_hex(char c) { return is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
		char lower(char c) { return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c; }

		bool starts_with_ci(std::string_view s, std::size_t pos, std::string_view word)
		{
			if (pos + word.size() > s.size())
				return false;
			for (std::size_t i = 0; i < word.size(); i++)
				if (lower(s[pos + i]) != word[i])
					return false;
			return true;
		}

		void replace_known(std::string& s, const scrubber::known& k)
		{
			if (k.text.size() < 3)
				return;
			const std::string label = "<" + k.label + ">";
			for (std::size_t pos = s.find(k.text); pos != std::string::npos; pos = s.find(k.text, pos))
			{
				// Short names (XMB user "Emma") only as whole words, so ordinary words aren't hit.
				const bool word = k.text.size() >= 8 ||
					((pos == 0 || !is_alnum(s[pos - 1])) && (pos + k.text.size() >= s.size() || !is_alnum(s[pos + k.text.size()])));
				if (!word)
				{
					pos += k.text.size();
					continue;
				}
				s.replace(pos, k.text.size(), label);
				pos += label.size();
			}
		}

		// C:\Users\<name>\ and /Users/<name>/ -> Users/<user>/
		void scrub_user_dirs(std::string& s)
		{
			for (std::size_t pos = 0; pos + 6 < s.size(); pos++)
			{
				if (!starts_with_ci(s, pos, "users") || (s[pos + 5] != '\\' && s[pos + 5] != '/'))
					continue;
				if (pos > 0 && s[pos - 1] != '\\' && s[pos - 1] != '/')
					continue;
				const std::size_t begin = pos + 6;
				std::size_t end = begin;
				while (end < s.size() && s[end] != '\\' && s[end] != '/' && s[end] != '"' && s[end] != '\'' && s[end] != '\n')
					end++;
				if (end == begin || s.compare(begin, end - begin, "<user>") == 0)
					continue;
				s.replace(begin, end - begin, "<user>");
				pos = begin + 6;
			}
		}

		bool email_local(char c) { return is_alnum(c) || c == '.' || c == '_' || c == '%' || c == '+' || c == '-'; }
		bool email_domain(char c) { return is_alnum(c) || c == '.' || c == '-'; }

		void scrub_emails(std::string& s)
		{
			for (std::size_t at = s.find('@'); at != std::string::npos; at = s.find('@', at + 1))
			{
				std::size_t b = at;
				while (b > 0 && email_local(s[b - 1]))
					b--;
				std::size_t e = at + 1;
				while (e < s.size() && email_domain(s[e]))
					e++;
				while (e > at + 1 && (s[e - 1] == '.' || s[e - 1] == '-'))
					e--;
				const std::string_view domain(s.data() + at + 1, e - at - 1);
				const std::size_t dot = domain.rfind('.');
				if (b == at || dot == std::string_view::npos || dot == 0 || domain.size() - dot < 3)
					continue;
				// The top-level domain is letters only: "68ms@285.82s" in the RSX hitch lines is a time, not an address.
				bool tld = true;
				for (std::size_t i = dot + 1; i < domain.size(); i++)
					tld = tld && is_alpha(domain[i]);
				if (!tld)
					continue;
				s.replace(b, e - b, "<email>");
				at = b + 6;
			}
		}

		// Parses up to four dot-separated numbers 0-255 at pos; returns the length or 0.
		std::size_t ipv4_at(const std::string& s, std::size_t pos, unsigned& first)
		{
			std::size_t i = pos;
			for (int part = 0; part < 4; part++)
			{
				if (part)
				{
					if (i >= s.size() || s[i] != '.')
						return 0;
					i++;
				}
				unsigned v = 0;
				std::size_t digits = 0;
				while (i < s.size() && is_digit(s[i]) && digits < 4)
				{
					v = v * 10 + static_cast<unsigned>(s[i] - '0');
					i++;
					digits++;
				}
				if (!digits || digits > 3 || v > 255)
					return 0;
				if (!part)
					first = v;
			}
			// Not part of a longer dotted number (1.2.3.4.5) or word.
			if (i < s.size() && (is_alnum(s[i]) || (s[i] == '.' && i + 1 < s.size() && is_digit(s[i + 1]))))
				return 0;
			return i - pos;
		}

		void scrub_ipv4(std::string& s)
		{
			for (std::size_t pos = 0; pos < s.size(); pos++)
			{
				if (!is_digit(s[pos]) || (pos > 0 && (is_alnum(s[pos - 1]) || s[pos - 1] == '.' || s[pos - 1] == '_')))
					continue;
				unsigned first = 0;
				const std::size_t len = ipv4_at(s, pos, first);
				if (!len)
				{
					while (pos + 1 < s.size() && (is_digit(s[pos + 1]) || s[pos + 1] == '.'))
						pos++;
					continue;
				}
				if (first == 0 || first == 127 || first >= 224)
				{
					pos += len - 1;
					continue;
				}
				s.replace(pos, len, "<ip>");
				pos += 3;
			}
		}

		// Runs of hex digits and colons: an IPv6 address with 5+ colons or "::" (and a digit), or a MAC.
		void scrub_ipv6_mac(std::string& s)
		{
			for (std::size_t pos = 0; pos < s.size(); pos++)
			{
				if (!(is_hex(s[pos]) || s[pos] == ':') || (pos > 0 && (is_alnum(s[pos - 1]) || s[pos - 1] == ':' || s[pos - 1] == '_')))
					continue;
				std::size_t end = pos, colons = 0, group = 0, max_group = 0;
				bool dbl = false, digit = false;
				while (end < s.size() && (is_hex(s[end]) || s[end] == ':'))
				{
					if (s[end] == ':')
					{
						colons++;
						dbl |= end > pos && s[end - 1] == ':';
						group = 0;
					}
					else
					{
						digit |= is_digit(s[end]);
						max_group = group + 1 > max_group ? group + 1 : max_group;
						group++;
					}
					end++;
				}
				if (end < s.size() && (is_alnum(s[end]) || s[end] == '_'))
				{
					pos = end;
					continue;
				}
				// Group lengths of 1-4 only (not hex dumps or C++ scopes like std::).
				const bool addr = max_group <= 4 && digit && (colons >= 5 || (dbl && colons >= 2 && end - pos >= 6));
				if (addr)
				{
					s.replace(pos, end - pos, "<addr>");
					pos += 5;
				}
				else
					pos = end;
			}
		}

		// password=..., token: ..., "password": "..." -> <redacted>
		void scrub_secrets(std::string& s)
		{
			static constexpr std::string_view words[] = {"password", "passwd", "token", "secret", "ticket", "authorization"};
			for (std::size_t pos = 0; pos < s.size(); pos++)
			{
				std::size_t wlen = 0;
				for (const auto w : words)
				{
					if (starts_with_ci(s, pos, w))
					{
						wlen = w.size();
						break;
					}
				}
				if (!wlen)
					continue;
				std::size_t i = pos + wlen;
				while (i < s.size() && (is_alpha(s[i]) || s[i] == '_'))
					i++; // "Password Hash", "token_value"
				while (i < s.size() && (s[i] == ' ' || s[i] == '"' || s[i] == '\''))
					i++;
				if (i >= s.size() || (s[i] != ':' && s[i] != '='))
				{
					pos = i > pos ? i - 1 : pos;
					continue;
				}
				i++;
				while (i < s.size() && (s[i] == ' ' || s[i] == '"' || s[i] == '\''))
					i++;
				std::size_t end = i;
				while (end < s.size() && s[end] != ' ' && s[end] != ',' && s[end] != '"' && s[end] != '\'' && s[end] != ';' && s[end] != '\n' && s[end] != '\r')
					end++;
				if (end > i && s.compare(i, end - i, "<redacted>") != 0)
				{
					s.replace(i, end - i, "<redacted>");
					end = i + 10;
				}
				pos = end;
			}
		}

		// The log channel of an RPCS3 log line ("·N 0:00:01.000000 {thread} rpcn: text"): RPCN, NP handler,
		// tickets, signaling, clans or the sceNp* modules.
		// Returns where the text after the channel starts (0: another channel); `hle` is set for sceNp*.
		std::size_t online_text(std::string_view s, bool& hle)
		{
			const std::size_t brace = s.find("} ");
			if (brace == std::string_view::npos)
				return 0;
			const std::size_t begin = brace + 2;
			std::size_t end = begin;
			while (end < s.size() && (is_alnum(s[end]) || s[end] == '_'))
				end++;
			if (end + 1 >= s.size() || s[end] != ':' || s[end + 1] != ' ')
				return 0;
			const std::string_view channel = s.substr(begin, end - begin);
			hle = channel.substr(0, 5) == "sceNp";
			static constexpr std::string_view online[] = {"rpcn", "UWPRPCN", "NPHandler", "Ticket", "Signaling", "clans", "clans_config", "np_gui_cache"};
			bool match = hle;
			for (const auto name : online)
				match |= channel == name;
			return match ? end + 2 : 0;
		}

		// Other players' names in RPCN / NP lines, after the channel: "quoted", (in parentheses) except in
		// sceNp* HLE call lines (their arguments are numbers and pointers), and the word after from/as.
		void scrub_online(std::string& s, std::size_t begin, bool hle)
		{
			std::string out(s, 0, begin);
			out.reserve(s.size());
			for (std::size_t i = begin; i < s.size(); i++)
			{
				const char c = s[i];
				if (c == '"' || (c == '(' && !hle))
				{
					const char close = c == '"' ? '"' : ')';
					const std::size_t end = s.find(close, i + 1);
					if (end != std::string::npos && end - i < 200)
					{
						out += c;
						out += "<redacted>";
						out += close;
						i = end;
						continue;
					}
				}
				if (i > begin && (s[i - 1] == ' ' || s[i - 1] == ',') && (starts_with_ci(s, i, "from") || starts_with_ci(s, i, "as")))
				{
					const std::size_t wlen = starts_with_ci(s, i, "from") ? 4 : 2;
					std::size_t j = i + wlen;
					if (j < s.size() && (s[j] == ' ' || s[j] == ':'))
					{
						out.append(s, i, j - i + 1);
						j++;
						std::size_t end = j;
						while (end < s.size() && (is_alnum(s[end]) || s[end] == '-' || s[end] == '_' || s[end] == '.'))
							end++;
						if (end > j)
							out += "<redacted>";
						i = end - 1;
						continue;
					}
				}
				out += c;
			}
			s.swap(out);
		}
	}

	std::string scrubber::scrub(std::string_view line) const
	{
		std::string s(line);
		for (const known& k : known_strings)
			replace_known(s, k);
		scrub_user_dirs(s);
		scrub_emails(s);
		scrub_secrets(s);
		bool hle = false;
		if (const std::size_t text = online_text(s, hle))
			scrub_online(s, text, hle);
		scrub_ipv6_mac(s);
		scrub_ipv4(s);
		return s;
	}
}
