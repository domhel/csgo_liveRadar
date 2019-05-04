#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "AssetManager.hpp"
#include "DEFINITIONS.hpp"
#ifdef CSGO
#include "MemoryManager.h"
#include "Manager.h"
#include "CsMap.hpp"
#include "CsWindow.hpp"
#include "CsLocalplayer.hpp"
dh::MemoryManager mem;
dh::Manager cm;
#endif
#ifdef SIM
#include "SimMap.hpp"
#include "SimPlayer.hpp"
#include "SimWindow.hpp"
#endif
#include <Windows.h>

AssetManager assets;

int main(void)
{
#ifdef CSGO
	HANDLE cmThread = NULL;
	DWORD cmThreadId = 5;
	cmThread = CreateThread(NULL, NULL, &dh::Manager::RunThread, (LPVOID)& cm, NULL, &cmThreadId);
	while (cm.me.address == NULL) Sleep(1);
	dh::CsMap map("de_cache");
	dh::CsWindow wnd(map, 900, 900);
	wnd.Run();

	cm.Stop();
#endif
#ifdef SIM
	dh::SimMap map("de_cache");
	map.addPlayer();
	dh::SimWindow wnd(map, 900, 900);
	wnd.Run();
#endif
	return 0;
}