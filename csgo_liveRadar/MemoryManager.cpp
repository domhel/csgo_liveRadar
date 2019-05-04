#include <SFML/Graphics.hpp>
#include "MemoryManager.h"
#ifdef CSGO
#include "offsets.hpp"
#include "CsLocalplayer.hpp"
#include "Manager.h"

dh::MemoryManager::MemoryManager() {
	processID = NULL;
	processHandle = NULL;
	try {
		if (!attachProcess("csgo.exe")) throw 1;
		this->clientModule = getModule("client_panorama.dll");
		this->engineModule = getModule("engine.dll");
		this->clientBase = (DWORD)clientModule.modBaseAddr;
		this->engineBase = (DWORD)engineModule.modBaseAddr;
		if (clientBase == 0x0) throw 2;
		if (engineBase == 0x0) throw 3;
		this->clientSize = clientModule.dwSize;
		this->engineSize = engineModule.dwSize;
	}
	catch (int iEx) {
		switch (iEx)
		{
		case 1:
			MessageBox(NULL, "CS:GO must be running", "ERROR", MB_ICONSTOP | MB_OK);
			exit(0);
			break;
		case 2:
			MessageBox(NULL, "Couldn't find Client.dll", "ERROR", MB_ICONSTOP | MB_OK);
			exit(0);
			break;
		case 3:
			MessageBox(NULL, "Couldn't find Engine.dll", "ERROR", MB_ICONSTOP | MB_OK);
			exit(0);
			break;
		default:
			throw;
		}
	}
	catch (...) {
		MessageBox(NULL, "Unhandled exception thrown", "ERROR", MB_ICONSTOP | MB_OK);
		exit(0);
	}
}
dh::MemoryManager::~MemoryManager()
{ 
	CloseHandle(processHandle); 
}

bool dh::MemoryManager::attachProcess(const char* processName)
{
	// take snapshot of current processes
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(processEntry);

	do {
		if (!strcmp(processEntry.szExeFile, processName))
		{
			this->processID = processEntry.th32ProcessID;
			CloseHandle(snapshot);
			this->processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processID);
			return true;
		}
	} while (Process32Next(snapshot, &processEntry));

	CloseHandle(snapshot);
	return false;
}
MODULEENTRY32 dh::MemoryManager::getModule(const char* moduleName)
{
	// take snapshot of current modules
	HANDLE hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->processID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	// find module with given modulename
	do {
		if (!strcmp(mEntry.szModule, moduleName))
		{
			CloseHandle(hModuleSnapshot);
			return mEntry;
		}
	} while (Module32Next(hModuleSnapshot, &mEntry));

	CloseHandle(hModuleSnapshot);
	mEntry.modBaseAddr = 0x0;
	return mEntry;
}
DWORD dh::MemoryManager::getProcessID(void) 
{ 
	return processID; 
}
HANDLE dh::MemoryManager::getProcessHandle(void) 
{ 
	return processHandle; 
}

DWORD dh::MemoryManager::getLocalplayer(void)
{
	return readMem<DWORD>(clientBase + hazedumper::signatures::dwLocalPlayer);
}
DWORD dh::MemoryManager::getEntityAddress(DWORD index)
{
	return readMem<DWORD>(clientBase + hazedumper::signatures::dwEntityList + (index - 1) * 0x10);
}
std::vector<DWORD> dh::MemoryManager::getAllEnemies(void)
{
	std::vector<DWORD> enemies;
	for (int i = 1; i < 32; ++i)
	{
		dh::CsPlayer currentEnemy;
		currentEnemy.updateAddress(i);
		if (currentEnemy.address == 0UL) continue;
		if (!currentEnemy.isEnemy() || !currentEnemy.isAlive()) continue;
		enemies.push_back(currentEnemy.address);
	}
	return enemies;
}
std::vector<DWORD> dh::MemoryManager::getAllTeammates(void)
{
	std::vector<DWORD> mates;
	for (int i = 1; i < 32; ++i)
	{
		dh::CsPlayer currentMate;
		currentMate.updateAddress(i);
		if (currentMate.address == 0UL || currentMate.address == cm.me.address) continue;
		if (!currentMate.isAlive() || currentMate.isEnemy()) continue;
		mates.push_back(currentMate.address);
	}
	return mates;
}
DWORD dh::MemoryManager::getClientState(void)
{
	return readMem<DWORD>(engineBase + hazedumper::signatures::dwClientState);
}
#endif