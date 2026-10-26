// RPCN account handling for the UWP menu. Mirrors rpcs3qt/rpcn_settings_dialog.cpp without Qt:
// same validation, same password derivation, same server calls and error texts.

#include "stdafx.h"
#include "uwp_rpcn.h"

#include "Emu/NP/rpcn_client.h"
#include "Emu/NP/rpcn_config.h"
#include "util/cctype.hpp"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif
#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/pwdbased.h>
#include <wolfssl/wolfcrypt/sha3.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <algorithm>

LOG_CHANNEL(rpcn_ui_log, "UWPRPCN");

namespace uwp_rpcn
{
	namespace
	{
		std::string state_text(rpcn::rpcn_state state)
		{
			switch (state)
			{
			case rpcn::rpcn_state::failure_no_failure: return "No error.";
			case rpcn::rpcn_state::failure_input: return "The server address is invalid.";
			case rpcn::rpcn_state::failure_wolfssl: return "The secure connection (TLS) couldn't be set up.";
			case rpcn::rpcn_state::failure_resolve: return "The server name couldn't be resolved. Check the console's internet connection.";
			case rpcn::rpcn_state::failure_binding: return "The connection couldn't be bound to a local address.";
			case rpcn::rpcn_state::failure_connect: return "The server didn't answer. Check the console's internet connection.";
			case rpcn::rpcn_state::failure_id: return "Login failed.";
			case rpcn::rpcn_state::failure_id_already_logged_in: return "This account is already logged in somewhere else.";
			case rpcn::rpcn_state::failure_id_username: return "There is no account with that username.";
			case rpcn::rpcn_state::failure_id_password: return "The password is wrong.";
			case rpcn::rpcn_state::failure_id_token: return "The account isn't activated yet: enter the token from the account email.";
			case rpcn::rpcn_state::failure_protocol: return "The server uses a newer RPCN protocol than this build.";
			case rpcn::rpcn_state::failure_other: return "Unknown RPCN error.";
			}
			return "Unknown RPCN error.";
		}

		// A fresh client (the singleton is dropped when the menu lets go of it, so an earlier
		// failure doesn't stick), connected to the configured server.
		std::shared_ptr<rpcn::rpcn_client> connect(result& res)
		{
			g_cfg_rpcn.load();
			auto rpcn = rpcn::rpcn_client::get_instance(0);
			if (const auto state = rpcn->wait_for_connection(); state != rpcn::rpcn_state::failure_no_failure)
			{
				rpcn_ui_log.error("Connecting to %s failed: %s", g_cfg_rpcn.get_host(), rpcn::rpcn_state_to_string(state));
				res = {false, "Couldn't connect to the RPCN server " + g_cfg_rpcn.get_host() + ".\n" + state_text(state)};
				return nullptr;
			}
			return rpcn;
		}
	}

	bool valid_username(std::string_view username)
	{
		if (username.length() < 3 || username.length() > 16)
			return false;

		return std::all_of(username.cbegin(), username.cend(), [](const char c)
		{
			return utils::isalnum(c) || c == '-' || c == '_';
		});
	}

	bool valid_email(std::string_view email)
	{
		// ^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*$ (the Qt dialog's check)
		const usz at = email.find('@');
		if (at == umax || at == 0 || at + 1 >= email.size() || email.find('@', at + 1) != umax)
			return false;

		constexpr std::string_view local_extra = ".!#$%&'*+/=?^_`{|}~-";
		const std::string_view local = email.substr(0, at);
		if (!std::all_of(local.begin(), local.end(), [&](char c) { return utils::isalnum(c) || local_extra.find(c) != umax; }))
			return false;

		const std::string_view domain = email.substr(at + 1);
		if (domain.front() == '.' || domain.back() == '.' || domain.find("..") != umax)
			return false;
		return std::all_of(domain.begin(), domain.end(), [](char c) { return utils::isalnum(c) || c == '-' || c == '.'; });
	}

	bool valid_token(std::string_view token)
	{
		return token.size() == 16 && std::all_of(token.cbegin(), token.cend(), [](const char c) { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'); });
	}

	std::string derive_password(std::string_view password)
	{
		constexpr std::string_view salt = "No matter where you go, everybody's connected.";

		u8 digest[WC_SHA3_256_DIGEST_SIZE];
		ensure(!wc_PBKDF2(digest, reinterpret_cast<const u8*>(password.data()), ::narrow<s32>(password.size()), reinterpret_cast<const u8*>(salt.data()), ::narrow<s32>(salt.size()), 200'000, WC_SHA3_256_DIGEST_SIZE, WC_SHA3_256));

		std::string derived(WC_SHA3_256_DIGEST_SIZE * 2, '0');
		for (u32 i = 0; i < WC_SHA3_256_DIGEST_SIZE; i++)
		{
			constexpr auto pal = "0123456789ABCDEF";
			derived[i * 2] = pal[digest[i] >> 4];
			derived[i * 2 + 1] = pal[digest[i] & 15];
		}
		return derived;
	}

	account get_account()
	{
		g_cfg_rpcn.load();
		account acc;
		acc.host = g_cfg_rpcn.get_host();
		// Not get_npid(): that invents and saves a random name when none is set.
		acc.npid = g_cfg_rpcn.npid.to_string();
		acc.has_password = !g_cfg_rpcn.get_password().empty();
		acc.has_token = !g_cfg_rpcn.get_token().empty();
		return acc;
	}

	void save_login(std::string_view npid, std::string_view password, std::string_view token)
	{
		g_cfg_rpcn.load();
		g_cfg_rpcn.set_npid(npid);
		g_cfg_rpcn.set_password(derive_password(password));
		g_cfg_rpcn.set_token(token);
		g_cfg_rpcn.save();
		rpcn_ui_log.notice("Saved the login of RPCN account %s", npid);
	}

	void save_token(std::string_view token)
	{
		g_cfg_rpcn.load();
		g_cfg_rpcn.set_token(token);
		g_cfg_rpcn.save();
	}

	void save_host(std::string_view host)
	{
		g_cfg_rpcn.load();
		g_cfg_rpcn.set_host(host);
		g_cfg_rpcn.save();
		rpcn_ui_log.notice("RPCN server set to %s", host);
	}

	void forget_account()
	{
		g_cfg_rpcn.load();
		g_cfg_rpcn.set_npid("");
		g_cfg_rpcn.set_password("");
		g_cfg_rpcn.set_token("");
		g_cfg_rpcn.save();
		rpcn_ui_log.notice("RPCN account removed from this console");
	}

	result create_account(std::string_view npid, std::string_view password, std::string_view email)
	{
		const std::string derived = derive_password(password);

		result res;
		{
			const auto rpcn = connect(res);
			if (!rpcn)
				return res;

			constexpr auto avatar_url = "https://rpcs3.net/cdn/netplay/DefaultAvatar.png";
			if (const auto error = rpcn->create_user(npid, derived, npid, avatar_url, email); error != rpcn::ErrorType::NoError)
			{
				rpcn_ui_log.error("Creating RPCN account %s failed: %s", npid, error);
				switch (error)
				{
				case rpcn::ErrorType::CreationExistingUsername: return {false, "An account with that username already exists."};
				case rpcn::ErrorType::CreationBannedEmailProvider: return {false, "This email provider is banned by the server."};
				case rpcn::ErrorType::CreationExistingEmail: return {false, "An account with that email already exists."};
				case rpcn::ErrorType::CreationError: return {false, "The server couldn't create the account."};
				default: return {false, fmt::format("The server couldn't create the account (%s).", error)};
				}
			}
		}

		g_cfg_rpcn.load();
		g_cfg_rpcn.set_npid(npid);
		g_cfg_rpcn.set_password(derived);
		g_cfg_rpcn.set_token("");
		g_cfg_rpcn.save();
		rpcn_ui_log.success("Created RPCN account %s", npid);
		return {true, {}};
	}

	result check_login()
	{
		const account acc = get_account();
		if (acc.npid.empty() || !acc.has_password)
			return {false, "No RPCN account is set up on this console."};

		result res;
		const auto rpcn = connect(res);
		if (!rpcn)
			return res;

		if (const auto state = rpcn->wait_for_authentified(); state != rpcn::rpcn_state::failure_no_failure)
		{
			rpcn_ui_log.error("Logging in as %s failed: %s", acc.npid, rpcn::rpcn_state_to_string(state));
			return {false, state_text(state)};
		}

		rpcn_ui_log.success("Logged in to RPCN as %s", acc.npid);
		return {true, rpcn->get_online_name()};
	}

	result resend_token()
	{
		const account acc = get_account();
		if (acc.npid.empty() || !acc.has_password)
			return {false, "No RPCN account is set up on this console."};

		result res;
		const auto rpcn = connect(res);
		if (!rpcn)
			return res;

		if (const auto error = rpcn->resend_token(acc.npid, g_cfg_rpcn.get_password()); error != rpcn::ErrorType::NoError)
		{
			rpcn_ui_log.error("Resending the token failed: %s", error);
			switch (error)
			{
			case rpcn::ErrorType::Invalid: return {false, "This server has no email verification and doesn't need a token."};
			case rpcn::ErrorType::DbFail: return {false, "A database error happened on the server."};
			case rpcn::ErrorType::TooSoon: return {false, "A token email can only be requested once every 24 hours."};
			case rpcn::ErrorType::EmailFail: return {false, "The server couldn't send the email."};
			case rpcn::ErrorType::LoginError: return {false, "The username or password is wrong."};
			default: return {false, fmt::format("Unknown error (%s).", error)};
			}
		}
		return {true, {}};
	}

	result send_reset_token(std::string_view npid, std::string_view email)
	{
		result res;
		const auto rpcn = connect(res);
		if (!rpcn)
			return res;

		if (const auto error = rpcn->send_reset_token(npid, email); error != rpcn::ErrorType::NoError)
		{
			rpcn_ui_log.error("Sending the password reset token failed: %s", error);
			switch (error)
			{
			case rpcn::ErrorType::Invalid: return {false, "This server has no email verification and doesn't support password changes."};
			case rpcn::ErrorType::DbFail: return {false, "A database error happened on the server."};
			case rpcn::ErrorType::TooSoon: return {false, "A reset token can only be requested once every 24 hours."};
			case rpcn::ErrorType::EmailFail: return {false, "The server couldn't send the email."};
			case rpcn::ErrorType::LoginError: return {false, "The username and email don't match an account."};
			default: return {false, fmt::format("Unknown error (%s).", error)};
			}
		}
		return {true, {}};
	}

	result reset_password(std::string_view npid, std::string_view token, std::string_view new_password)
	{
		const std::string derived = derive_password(new_password);

		result res;
		{
			const auto rpcn = connect(res);
			if (!rpcn)
				return res;

			if (const auto error = rpcn->reset_password(npid, token, derived); error != rpcn::ErrorType::NoError)
			{
				rpcn_ui_log.error("Changing the password failed: %s", error);
				switch (error)
				{
				case rpcn::ErrorType::Invalid: return {false, "This server has no email verification and doesn't support password changes."};
				case rpcn::ErrorType::DbFail: return {false, "A database error happened on the server."};
				case rpcn::ErrorType::TooSoon: return {false, "The password can only be changed once every 24 hours."};
				case rpcn::ErrorType::LoginError: return {false, "The username and reset token don't match."};
				default: return {false, fmt::format("Unknown error (%s).", error)};
				}
			}
		}

		g_cfg_rpcn.load();
		g_cfg_rpcn.set_npid(npid);
		g_cfg_rpcn.set_password(derived);
		g_cfg_rpcn.save();
		rpcn_ui_log.success("Changed the password of RPCN account %s", npid);
		return {true, {}};
	}

	namespace
	{
		std::shared_ptr<rpcn::rpcn_client> login(result& res)
		{
			const account acc = get_account();
			if (acc.npid.empty() || !acc.has_password)
			{
				res = {false, "No RPCN account is set up on this console. Set one up in Settings > RPCN account."};
				return nullptr;
			}
			const auto rpcn = connect(res);
			if (!rpcn)
				return nullptr;
			if (const auto state = rpcn->wait_for_authentified(); state != rpcn::rpcn_state::failure_no_failure)
			{
				rpcn_ui_log.error("Logging in as %s failed: %s", acc.npid, rpcn::rpcn_state_to_string(state));
				res = {false, state_text(state)};
				return nullptr;
			}
			return rpcn;
		}
	}

	result get_friends(friends& out)
	{
		out = {};
		result res;
		const auto rpcn = login(res);
		if (!rpcn)
			return res;

		rpcn::friend_data data;
		rpcn->get_friends(data);
		for (const auto& [name, f] : data.friends)
			out.list.push_back({name, f.online, f.online ? f.pr_title : std::string()});
		std::stable_partition(out.list.begin(), out.list.end(), [](const friend_entry& f) { return f.online; });
		out.requests_received.assign(data.requests_received.begin(), data.requests_received.end());
		out.requests_sent.assign(data.requests_sent.begin(), data.requests_sent.end());
		out.blocked.assign(data.blocked.begin(), data.blocked.end());
		return {true, {}};
	}

	result add_friend(std::string_view npid)
	{
		result res;
		const auto rpcn = login(res);
		if (!rpcn)
			return res;

		const std::optional<rpcn::ErrorType> error = rpcn->add_friend(npid);
		if (!error)
			return {false, "The RPCN server didn't answer."};
		switch (*error)
		{
		case rpcn::ErrorType::NoError: rpcn_ui_log.success("Friend request to %s", npid); return {true, {}};
		case rpcn::ErrorType::NotFound: return {false, fmt::format("There is no RPCN user named %s.", npid)};
		case rpcn::ErrorType::AlreadyFriend: return {false, fmt::format("%s is already a friend or has a request from you.", npid)};
		default: return {false, fmt::format("The server refused it (%s).", *error)};
		}
	}

	result remove_friend(std::string_view npid)
	{
		result res;
		const auto rpcn = login(res);
		if (!rpcn)
			return res;
		if (!rpcn->remove_friend(npid))
			return {false, fmt::format("The server didn't remove %s.", npid)};
		rpcn_ui_log.success("Removed %s from the friends", npid);
		return {true, {}};
	}
}
