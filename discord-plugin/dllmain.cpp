#include "dllmain.h"

void MainThread()
{
	while (*(DWORD*)0xC8D4C0 != 9)
		Sleep(350);

	pGame = new Game();
	std::string details, smallImageText, largeImageText;
	// int partySize, partyMax;

	DiscordRichPresence drp;

	drp = { 0 };
	drp.startTimestamp = time(0);

	Discord_Initialize(APPLICATION_ID, 0, 0, 0);
	
	if (GetModuleHandleA("samp.dll"))
	{
		pSamp = new Samp();

		// SA-MP
		while (!pSamp->Init())
			Sleep(350);

		// Getting samp values
		std::string serverIP = pSamp->GetServerIp();
		std::string serverName = cp1251_to_utf8(pSamp->GetServerName().c_str()); // 

		// Getting player information
		if (!pSamp->GetPlayerPool())
			return;

		int playerId = pSamp->GetPlayerPool()->sLocalPlayerID;
		std::string playerName = cp1251_to_utf8(pSamp->GetPlayerPool()->strLocalPlayerName.c_str()); // 

		drp.smallImageKey = "samp_icon";

		// Loop
		while (1 < 2)
		{
			if (pGame->IsPedExists())
			{
				details = playerName + " [" + std::to_string(playerId) + "]";
				largeImageText = "Location: " + pGame->GetCurrentZone();
				smallImageText = "Playing SAMP";

				// Sending data
				drp.largeImageKey = weaponIcons[pGame->GetCurrentWeapon()].c_str();
				drp.largeImageText = largeImageText.c_str();
				drp.smallImageText = smallImageText.c_str();
				drp.details = details.c_str();
				drp.state = serverName.c_str();

				Discord_UpdatePresence(&drp);

				Sleep(15000);
			}
		}
	}
	else
	{
		// Single Player
		//char state[256];
		std::string state;
		drp.smallImageKey = "game_icon";

		// Loop
		while (1 < 2)
		{
			if (pGame->IsPedExists())
			{
				if (pGame->IsInVehicle()) {
					if (pGame->GetVehicleID() >= 400 && pGame->GetVehicleID() <= 611) details = "Vehicle: " + vehNames[pGame->GetVehicleID() - 400];
					else details = "Hm, not sure what that vehicle is!";
					state = "Radio: " + radioNames[pGame->GetCurrentRadio()];
				}
				else {
					details = "Not in a vehicle!";
					state = "";
				}
												
				largeImageText = "Location: " + pGame->GetCurrentZone();
				smallImageText = std::to_string(pGame->GetPassedDays()) + " day(s) passed.";
				//smallImageText = "Radio: " + std::to_string(pGame->GetCurrentRadio());

				// Sending data
				drp.largeImageKey = weaponIcons[pGame->GetCurrentWeapon()].c_str();
				drp.largeImageText = largeImageText.c_str();
				drp.smallImageText = smallImageText.c_str();
				drp.details = details.c_str();
				drp.state = state.c_str();

				Discord_UpdatePresence(&drp);

				Sleep(15000);
			}
		}
	}
}

std::string cp1251_to_utf8(const char* str)
{
	std::string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t* ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char* cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), 0, 0, 0);
	}
	else if (reason == DLL_PROCESS_DETACH)
        Discord_Shutdown();

	return TRUE;
}