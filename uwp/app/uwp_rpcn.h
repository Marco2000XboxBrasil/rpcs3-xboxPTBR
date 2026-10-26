#pragma once

// RPCN (RPCS3's PSN replacement) account handling for the UWP menu, in place of the Qt UI's
// rpcn_settings_dialog: account creation, login check, tokens and password reset.
// The calls that talk to the server block (connect + TLS handshake, a few seconds at most);
// run them on a worker thread while no game is running.

#include <string>
#include <vector>
#include <string_view>

namespace uwp_rpcn
{
	struct result
	{
		bool ok = false;
		std::string message; // for the user
	};

	// Same rules as the Qt dialogs.
	bool valid_username(std::string_view username);
	bool valid_email(std::string_view email);
	bool valid_token(std::string_view token);

	// What rpcn.yml stores as the password: PBKDF2-SHA3-256 of the typed one (as desktop RPCS3).
	std::string derive_password(std::string_view password);

	// Account state from rpcn.yml (reloaded on each call).
	struct account
	{
		std::string host;
		std::string npid; // empty: no account set up
		bool has_password = false;
		bool has_token = false;
	};
	account get_account();

	// Saves an existing account's login (password as typed; token may be empty) without checking it.
	void save_login(std::string_view npid, std::string_view password, std::string_view token);
	void save_token(std::string_view token);
	void save_host(std::string_view host);
	void forget_account();

	// Server calls (blocking).
	result create_account(std::string_view npid, std::string_view password, std::string_view email);
	result check_login(); // connects and logs in with the saved account
	result resend_token();
	result send_reset_token(std::string_view npid, std::string_view email);
	result reset_password(std::string_view npid, std::string_view token, std::string_view new_password);

	// The friends list (pause menu), as RPCS3's friends overlay shows it.
	struct friend_entry
	{
		std::string name;
		bool online = false;
		std::string playing; // presence title while online
	};
	struct friends
	{
		std::vector<friend_entry> list; // online first
		std::vector<std::string> requests_received, requests_sent, blocked;
	};
	result get_friends(friends& out); // logs in with the saved account
	result add_friend(std::string_view npid); // a request, or accepts the other user's request
	result remove_friend(std::string_view npid); // also rejects or cancels a request
}
