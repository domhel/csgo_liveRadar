#pragma once

#include "DEFINITIONS.hpp"
#ifdef CSGO
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

namespace dh {	
	class MemoryManager
	{
	private:
		HANDLE processHandle;
		DWORD processID;

	public:
		MODULEENTRY32 clientModule;
		MODULEENTRY32 engineModule;
		DWORD clientBase, clientSize;
		DWORD engineBase, engineSize;

		MemoryManager();
		~MemoryManager();
		bool attachProcess(const char* processName);
		MODULEENTRY32 getModule(const char* moduleName);

		DWORD getProcessID(void);
		HANDLE getProcessHandle(void);
		template <typename c> c readMem(DWORD address) {
			c value;
			ReadProcessMemory(processHandle, (LPCVOID)address, &value, sizeof(c), NULL);
			return value;
		}
		template <typename c> bool writeMem(DWORD address, c value){
			return WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(c), NULL);
		}
		std::vector<DWORD> getAllEnemies(void);
		std::vector<DWORD> getAllTeammates(void);
		DWORD getEntityAddress(DWORD index);
		DWORD getClientState(void);
		DWORD getLocalplayer(void);
	}; 
} // namespace dh
extern dh::MemoryManager mem;
#endif