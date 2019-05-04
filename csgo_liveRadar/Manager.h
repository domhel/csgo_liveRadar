#pragma once

#include "DEFINITIONS.hpp"
#ifdef CSGO
#include "CsLocalplayer.hpp"

namespace dh {
	class CsLocalplayer;
	class Manager
	{
	private:
		bool running;
	public:
		CsLocalplayer me;
		Manager();
		~Manager();

		void Update(void);
		static DWORD WINAPI RunThread(LPVOID param);
		void Stop(void);
	};
}
#include "DEFINITIONS.hpp"
extern dh::Manager cm;
#endif