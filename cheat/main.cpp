#include "gui.h"
#include "hacks.h"
#include "globals.h"
#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// initialize memory class
	const auto mem = Memory{ "csgo.exe" };

	// module addresses
	globals::clientAddress = mem.GetModuleAddress("client.dll");
	globals::engineAddress = mem.GetModuleAddress("engine.dll");

	std::thread(hacks::VisualsThread, mem).detach();


	// create gui
	gui::CreateHWindow("Cheat Menu");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}
