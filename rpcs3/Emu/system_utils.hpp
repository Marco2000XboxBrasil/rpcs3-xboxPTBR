#pragma once

#include "util/types.hpp"
#include <string>
#include <string_view>
#include <set>
#include <vector>
#include <utility>

struct GameInfo;

enum class game_content_type
{
	content_icon,         // ICON0.PNG
	content_video,        // ICON1.PAM
	content_sound,        // SND0.AT3
	overlay_picture,      // PIC0.PNG (16:9) or PIC2.PNG (4:3)
	background_picture,   // PIC1.PNG
	background_picture_2, // PIC3.PNG (should only exist for install or extra content discs...)
};

namespace rpcs3::utils
{
	u32 get_max_threads();

#ifdef RPCS3_UWP
	// Set by the UWP shell: the app's memory use, and its limit through `limit`, in bytes.
	extern u64 (*g_uwp_app_memory)(u64* limit);

	// Held around one LLVM compile job (a PPU module or an SPU function). The Xbox ends an app
	// silently once it goes over its memory limit, and parallel PPU compiles of a big game
	// (Portal 2) can get there; a new job waits while less than the headroom (plus a share per
	// running job) is left, unless nothing else is compiling. LocalState/compile_headroom sets the
	// headroom in MB.
	struct uwp_compile_gate
	{
		uwp_compile_gate();
		~uwp_compile_gate();
		uwp_compile_gate(const uwp_compile_gate&) = delete;
		uwp_compile_gate& operator=(const uwp_compile_gate&) = delete;

		static inline u32 headroom_mb = 1280;
		// Counted for each job already running (they grow after they start). LocalState/compile_job_mb.
		static inline u32 job_mb = 128;

		// Peak app memory seen by the gate and total time jobs waited, since the last call.
		static std::pair<u64, u64> take_stats();
	};
#endif

	void configure_logs(bool force_enable = false);

	u32 check_user(std::string_view user);

	bool install_pkg(const std::string& path, bool from_optical_drive);

	// VFS directories and disk usage
	std::vector<std::pair<std::string, u64>> get_vfs_disk_usage();
	std::string get_emu_dir();
	std::string get_hdd0_dir();
	std::string get_hdd1_dir();
	std::string get_flash_dir();
	std::string get_flash2_dir();
	std::string get_flash3_dir();
	std::string get_bdvd_dir();
	std::string get_games_dir();

	std::string get_hdd0_game_dir();
	std::string get_hdd0_locks_dir();
	std::string get_hdd1_cache_dir();
	std::string get_games_shortcuts_dir();

	// Cache directories and disk usage
	u64 get_cache_disk_usage();
	std::string get_cache_dir();
	std::string get_cache_dir(std::string_view module_path);

	std::string	get_redump_db_path();
	std::string get_redump_db_download_url();
	std::string get_redump_key_dir();
	std::string get_psn_content_db_path();
	std::string get_psn_content_db_download_url();
	std::string get_psn_dlc_db_path();
	std::string get_psn_dlc_db_download_url();
	std::string get_psn_update_db_path();
	std::string get_psn_update_db_download_url();

	std::string get_data_dir();
	std::string get_icons_dir();
#ifdef RPCS3_UWP
	extern std::string g_uwp_savestates_dir;
#endif
	std::string get_savestates_dir();
	std::string get_captures_dir();
	std::string get_recordings_dir();
	std::string get_screenshots_dir();

	// get_cache_dir_by_serial() named in this way to avoid conflict (wrong invocation) with get_cache_dir()
	std::string get_cache_dir_by_serial(const std::string& serial);
	std::string get_data_dir(const std::string& serial);
	std::string get_icons_dir(const std::string& serial);
	std::string get_savestates_dir(const std::string& serial);
	std::string get_recordings_dir(const std::string& serial);
	std::string get_screenshots_dir(const std::string& serial);

	std::set<std::string> get_dir_list(const std::string& base_dir, const std::string& serial);
	std::set<std::string> get_file_list(const std::string& base_dir, const std::string& serial);

	std::string get_rap_file_path(const std::string_view& rap);
	bool verify_c00_unlock_edat(const std::string_view& content_id, bool fast = false);
	std::string get_sfo_dir_from_game_path(const std::string& game_path, const std::string& title_id = "");

	// Check whether "name" is the name of an additional disc game directory (e.g. "PS3_GM01"), the counterpart of "PS3_GAME".
	// NOTE: equivalent to the "^PS3_GM[[:digit:]]{2}$" regular expression, without building one for each checked name
	inline bool is_ps3_gm_dir_name(std::string_view name)
	{
		return name.size() == 8 && name.starts_with("PS3_GM") && name[6] >= '0' && name[6] <= '9' && name[7] >= '0' && name[7] <= '9';
	}

	std::string get_custom_config_dir();
	std::string get_custom_config_path(const std::string& identifier);

	std::string get_input_config_root();
	std::string get_input_config_dir(const std::string& title_id = "");
	std::string get_custom_input_config_path(const std::string& title_id);

	std::pair<std::string, bool> get_game_content_path(game_content_type type, const GameInfo& info);
	std::string get_game_content_path(game_content_type type);

	bool version_is_bigger(std::string_view v0, std::string_view v1, std::string_view serial, bool is_fw);
}
