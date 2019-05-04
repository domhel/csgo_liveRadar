#include <SFML/Graphics.hpp>
#include "CsLocalplayer.hpp"
#ifdef CSGO
#include <TlHelp32.h>
#include "Manager.h"

dh::Manager::Manager()
{
	running = false;
}
dh::Manager::~Manager()
{
}
void dh::Manager::Update(void)
{
	me.updateAddress();
}
DWORD WINAPI dh::Manager::RunThread(LPVOID param)
{
	Manager* This = (Manager*)param;
	This->running = true;
	int i = 10;
	while (This->running)
	{
		if (i == 10) {
			This->Update();
			i = 0;
		}
		++i;
		Sleep(10);
	}

	return 0;
}
void dh::Manager::Stop(void)
{
	running = false;
}
#endif