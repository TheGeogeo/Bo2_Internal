#pragma once

#include "Includes.h"

namespace SDK
{
	uintptr_t t6zm = (uintptr_t)GetModuleHandle(L"t6zm.exe");

	uintptr_t gClient = 0x2510ED4;
	int gClientHealth = 0x1A8;
	int gClientMaxhealth = 0x1AC;

	uintptr_t gClientStat = 0x8;
	int gClientStatName = 0x44;
	int gClientStatNameLen = 16;
	int gClientStatPoint = 0xD8;
	int gClientStatKill = 0xDC;
	int gClientStatDisplay = 0xF0;

	uintptr_t gClientInfo = 0x10;
	int gClientInfoPosition = 0x28;
	int gClientInfoCameraReadOnly = 0x1F8;
	int gClientInfoVelocity = 0x34;
	int gClientInfoWeaponList = 0x428;
	int gClientInfoWeaponListSize = 8;

	uintptr_t zombieEntList = 0x2A7E4F0;
	int zombieEntListSize = 0x31C;
	int zombieEntListHealth = 0x2F8;
	int zombieEntListMaxHealth = 0x2FC;
	int zombieEntListPosition = 0x284;
}