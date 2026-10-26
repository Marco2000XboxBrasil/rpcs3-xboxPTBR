// Host test for the telemetry log filter:
//   c++ -std=c++20 -I uwp/app uwp/app/uwp_telemetry_scrub.cpp uwp/app/test/telemetry_scrub_test.cpp -o /tmp/scrub_test && /tmp/scrub_test

#include "uwp_telemetry_scrub.h"

#include <cstdio>

int main()
{
	uwp_telemetry::scrubber sc;
	sc.known_strings = {{"EmelinH", "npid"}, {"AB12CD34EF56GH78", "rpcn_token"}, {"Emma", "username"}};

	struct test_case { const char* in; const char* out; };
	static constexpr test_case cases[] =
	{
		{"·! 0:00:01.234567 {rpcs3} rpcn: You are now logged in RPCN(EmelinH | EmelinH)!", "·! 0:00:01.234567 {rpcs3} rpcn: You are now logged in RPCN(<redacted>)!"},
		{"·S 0:00:02.000000 SYS: user EmelinH token AB12CD34EF56GH78", "·S 0:00:02.000000 SYS: user <npid> token <rpcn_token>"},
		{"SYS: Emma played, Emmanuel too", "SYS: <username> played, Emmanuel too"},
		{"SYS: Path: C:\\Users\\Emelin\\AppData\\Local\\Packages\\x", "SYS: Path: C:\\Users\\<user>\\AppData\\Local\\Packages\\x"},
		{"SYS: /home/a and C:/users/bob/x", "SYS: /home/a and C:/users/<user>/x"},
		{"·N 0:00:01.0 {TID: 1} UWPRPCN: account created for me.name+x@mail.example.de now", "·N 0:00:01.0 {TID: 1} UWPRPCN: account created for <email> now"},
		{"RSX: UWP hitches: 2 in 10 s 68ms@285.82s(mem 1402, ovl 71 ms ago) 101ms@293.02s(mem 401, ovl 4 ms ago)", "RSX: UWP hitches: 2 in 10 s 68ms@285.82s(mem 1402, ovl 71 ms ago) 101ms@293.02s(mem 401, ovl 4 ms ago)"},
		{"NET: bound 192.168.1.23:3658 and 10.0.0.1, local 127.0.0.1, any 0.0.0.0", "NET: bound <ip>:3658 and <ip>, local 127.0.0.1, any 0.0.0.0"},
		{"SYS: RPCS3Xbox 0.1.34.72, firmware 4.93, v1.2.3.4", "SYS: RPCS3Xbox 0.1.34.72, firmware 4.93, v1.2.3.4"},
		{"NET: ip 2a02:8108:1c0:2e00:1234:5678:9abc:def0 mac 00:1a:2b:3c:4d:5e", "NET: ip <addr> mac <addr>"},
		{"NET: v6 fe80::1c2b:3a4d%12", "NET: v6 <addr>%12"},
		{"·! 0:12:34.567890 {PPU[0x1000000] main} sys_fs: std::string fs::get_cache_dir()", "·! 0:12:34.567890 {PPU[0x1000000] main} sys_fs: std::string fs::get_cache_dir()"},
		{"RPCN config: Password: deadbeef1234 Token=XYZ, \"password\": \"hunter2\"", "RPCN config: Password: <redacted> Token=<redacted>, \"password\": \"<redacted>\""},
		{"·N 0:00:03.0 {rpcs3} rpcn: Received message from FriendGuy:", "·N 0:00:03.0 {rpcs3} rpcn: Received message from <redacted>:"},
		{"·N 0:00:03.0 {rpcs3} rpcn: add_friend(\"Bob\") failed", "·N 0:00:03.0 {rpcs3} rpcn: add_friend(<redacted>) failed"},
		{"·N 0:00:04.0 {rpcs3} NPHandler: basic_event: event:1, from:SomeOne(Some One), size:4", "·N 0:00:04.0 {rpcs3} NPHandler: basic_event: event:1, from:<redacted>(<redacted>), size:4"},
		{"·W 0:00:19.4 {PPU[0x1000000] Thread (main) [HLE:0x020a0fe4]} sceNp: sceNpInit(poolsize=0x100000, poolptr=*0x1)", "·W 0:00:19.4 {PPU[0x1000000] Thread (main) [HLE:0x020a0fe4]} sceNp: sceNpInit(poolsize=0x100000, poolptr=*0x1)"},
		{"SYS: Failed to connect to the token server", "SYS: Failed to connect to the token server"},
	};

	int failed = 0;
	for (const auto& c : cases)
	{
		const std::string got = sc.scrub(c.in);
		if (got != c.out)
		{
			std::printf("FAIL\n  in:   %s\n  want: %s\n  got:  %s\n", c.in, c.out, got.c_str());
			failed++;
		}
	}
	std::printf("%d of %zu failed\n", failed, sizeof(cases) / sizeof(cases[0]));
	return failed != 0;
}
