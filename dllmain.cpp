#include "Includes.h"

struct Variables
{
	ent* gCliEnt = (ent*)(SDK::t6zm + SDK::gClient);
	uintptr_t* gCli = (uintptr_t*)(SDK::t6zm + SDK::gClient);
	uintptr_t* gCliStat = (uintptr_t*)(SDK::t6zm + SDK::gClient + SDK::gClientStat);
	uintptr_t* gCliInfo = (uintptr_t*)(SDK::t6zm + SDK::gClient + SDK::gClientInfo);

	uintptr_t* baseZombEntList = (uintptr_t*)(SDK::t6zm + SDK::zombieEntList);

	int distanceZombieTp = 150;
	Vec3 saveTp;

	bool inMenu = false;
	bool godMode = false;
	bool point = false;
	bool infAmmo = false;
	bool tpZombie = false;
	bool instakill = false;
}var;

void UI() {
	system("cls");
	const char* god = var.godMode ? "ON" : "OFF";
	const char* point = var.point ? "ON" : "OFF";
	const char* infAmmo = var.infAmmo ? "ON" : "OFF";
	const char* tpZom = var.tpZombie ? "ON" : "OFF";
	const char* instakill = var.instakill ? "ON" : "OFF";

	if (!var.inMenu)
		std::cout << "Hey " << var.gCliEnt->entPlayerStatPtr->name << " don't cheat like a kid!" << std::endl;
	else
		std::cout << "You are in menu you can't use this cheat." << std::endl;

	std::cout << "" << std::endl;
	std::cout << "NUMPAD0 / GodMode >> " << god << std::endl;
	std::cout << "NUMPAD1 / Inf Point >> " << point << std::endl;
	std::cout << "NUMPAD2 / Inf Ammo/Grenade >> " << infAmmo << std::endl;
	std::cout << "NUMPAD3 / Save TP | NUMPAD4 / TP to save {x:" << var.saveTp.x << " y: " << var.saveTp.y << " z: " << var.saveTp.z << "}" << std::endl;
	std::cout << "NUMPAD9 / Add 1k kill" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "F1 / TP Zombies >> " << tpZom << " | TP distance " << var.distanceZombieTp << " PAGE UP/PAGE DOWN" << std::endl;
	std::cout << "F2 / InstaKill >> " << instakill << std::endl;
	std::cout << "" << std::endl;
	std::cout << "END / Unload" << std::endl;
}

DWORD WINAPI MainHack(HMODULE hModule) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	SetConsoleTitle(L"Internal cheat BO2, TheGeogeo");
	UI();

	while (true)
	{
		if (var.gCliEnt->entPlayerStatPtr->name[0] == '\0')
		{
			if (!var.inMenu)
			{
				var.inMenu = true;
				var.godMode = false;
				var.point = false;
				var.infAmmo = false;
				var.tpZombie = false;
				var.instakill = false;
				UI();
			}
		}
		else {
			if (var.inMenu)
			{
				var.inMenu = false;
				UI();
			}

			if (GetAsyncKeyState(VK_NUMPAD0) & 1)
			{
				var.godMode = !var.godMode;
				UI();
			}

			if (GetAsyncKeyState(VK_NUMPAD1) & 1)
			{
				var.point = !var.point;
				UI();
			}

			if (GetAsyncKeyState(VK_NUMPAD2) & 1)
			{
				var.infAmmo = !var.infAmmo;
				UI();
			}

			if (GetAsyncKeyState(VK_NUMPAD3) & 1)
			{
				var.saveTp = var.gCliEnt->entPlayerInfoPtr->coords;
				UI();
			}

			if (GetAsyncKeyState(VK_NUMPAD4) & 1)
			{
				var.gCliEnt->entPlayerInfoPtr->coords = var.saveTp;
			}

			if (GetAsyncKeyState(VK_NUMPAD9) & 1)
			{
				var.gCliEnt->entPlayerStatPtr->kill += 1000;
				var.gCliEnt->entPlayerStatPtr->killDisplay = var.gCliEnt->entPlayerStatPtr->kill;
			}

			if (GetAsyncKeyState(VK_F1) & 1)
			{
				var.tpZombie = !var.tpZombie;
				UI();
			}

			if (GetAsyncKeyState(VK_F2) & 1)
			{
				var.instakill = !var.instakill;
				UI();
			}

			if (GetAsyncKeyState(VK_PRIOR) & 1)
			{
				if (var.distanceZombieTp < (MAXINT - 5))
					var.distanceZombieTp += 5;

				UI();
			}

			if (GetAsyncKeyState(VK_NEXT) & 1)
			{
				if ((var.distanceZombieTp - 5) > 0)
					var.distanceZombieTp -= 5;
				UI();
			}

			if (var.godMode)
			{
				/*int* health = (int*)(*var.gCli + SDK::gClientHealth);
				*health = 1000;*/
				var.gCliEnt->entPlayerPtr->health = 1000;
			}

			if (var.point)
			{
				/*int* point = (int*)(*var.gCliStat + SDK::gClientStatPoint);
				*point = 100000;*/
				var.gCliEnt->entPlayerStatPtr->point = 100000;
			}

			if (var.infAmmo)
			{
				int sizeArr = sizeof(var.gCliEnt->entPlayerInfoPtr->weaponList) / sizeof(var.gCliEnt->entPlayerInfoPtr->weaponList[0]);
				for (int i = 0; i < sizeArr; i++)
				{
					var.gCliEnt->entPlayerInfoPtr->weaponList[i] = 100;
				}
			}

			if (var.tpZombie)
			{
				for (int i = 0; i < 90; i++)
				{
					Vec3* enemyPos = (Vec3*)(*var.baseZombEntList + SDK::zombieEntListPosition + i * SDK::zombieEntListSize);
					if (enemyPos == nullptr) continue;

					// gets current player position
					Vec2* pitchYaw = (Vec2*)(*var.gCliInfo + SDK::gClientInfoCameraReadOnly);

					// convert degrees to pos
					double  pitch = -ConvertToRadians(pitchYaw->x);
					double  yaw = ConvertToRadians(pitchYaw->y);
					float x = (float)(cos(yaw) * cos(pitch));
					float y = (float)(sin(yaw) * cos(pitch));
					float z = (float)(sin(pitch));

					// get pos and set pos
					Vec3* myPos = (Vec3*)(*var.gCliInfo + SDK::gClientInfoPosition);
					Vec3 newEnemyPos = *myPos + Vec3{ x , y ,z } *var.distanceZombieTp;

					*enemyPos = newEnemyPos;
				}
			}

			if (var.instakill)
			{
				for (int i = 0; i < 90; i++)
				{
					int* health = (int*)(*var.baseZombEntList + SDK::zombieEntListHealth + i * SDK::zombieEntListSize);
					int* maxHealth = (int*)(*var.baseZombEntList + SDK::zombieEntListMaxHealth + i * SDK::zombieEntListSize);
					if (health == nullptr) continue;

					*health = 1;
					*maxHealth = 1;
				}
			}
		}

		if (GetAsyncKeyState(VK_END) & 1)
		{
			break;
		}
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = nullptr;
		hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainHack, hModule, NULL, NULL);
		if (hThread) {
			CloseHandle(hThread);
		}
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}