#pragma once

// The UWP XAML front end: the app menu (games, installs, settings), progress and error screens and
// the in-game pause menu, built from the XAML pages in uwp/app/xaml/ with Windows.UI.Xaml.
//
// There is no XAML compiler on the Linux build host, so the pages are parsed at run time with
// XamlReader and wired up through hand-written WinRT ABI calls (winrt_xaml_abi.h is generated from
// the SDK metadata). The game picture is shown through a SwapChainPanel that the render thread of
// the shell presents into.

#include "util/types.hpp"

#include <functional>
#include <string>

struct IDXGISwapChain1;

namespace uwp_xaml
{
	// What the shell wants shown over the menu; polled on every UI tick (UI thread).
	struct overlay_state
	{
		bool loading = false;           // boot / compile progress screen
		bool loading_over_game = false; // there is a game picture behind it: translucent backdrop
		std::string loading_title, loading_detail;
		u32 loading_done = 0, loading_total = 0; // total == 0: no progress bar value
		bool error = false;                       // fatal emulator error screen
		std::string error_text;
	};

	struct host
	{
		// UI thread: creates the composition swap chain the game panel shows. The caller owns the reference.
		std::function<IDXGISwapChain1*()> create_swap_chain;
		// UI thread, once the window is up: starts the emulator and render threads.
		std::function<void()> launched;
		// UI thread, every tick.
		std::function<void(overlay_state&)> poll_overlay;
		// UI thread: Application.Suspending / Resuming (Xbox Home and back).
		std::function<void()> suspending, resuming;
		// WinUI 2 (Microsoft.UI.Xaml 2.8 framework package) styles for the controls: the Windows 11 look.
		bool winui_styles = true;
	};

	// Runs the XAML application on the calling thread (Application.Start); returns when the app exits.
	int run(const host& h);

	// Any thread: the PS button (View + Menu) was pressed in a game; the pause menu opens on the next UI tick.
	void request_pause_menu();
}
