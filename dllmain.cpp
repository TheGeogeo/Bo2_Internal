#include "Includes.h"

DWORD WINAPI MainHack(HMODULE hModule) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	SetConsoleTitle(L"Internal cheat BO2, TheGeogeo");

	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			var.godMode = !var.godMode;
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			var.point = !var.point;
		}

		if (GetAsyncKeyState(VK_F1) & 1)
		{
			var.tpZombie = !var.tpZombie;
		}

		if (GetAsyncKeyState(VK_END) & 1)
		{
			break;
		}

		if (var.godMode)
		{
			int* health = (int*)(*var.gCli + SDK::gClientHealth);
			*health = 1000;
		}

		if (var.point)
		{
			int* point = (int*)(*var.gCliStat + SDK::gClientStatPoint);
			*point = 100000;
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
				Vec3 newEnemyPos = *myPos + Vec3{ x , y ,z } *150; // 150 is distance

				*enemyPos = newEnemyPos;
			}
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