#pragma once

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class EntPlayer
{
public:
	union
	{
		DEFINE_MEMBER_N(int, health, 0x1A8);
		DEFINE_MEMBER_N(int, maxHealth, 0x1AC);
	};
};

class entPlayerStat
{
public:
	union
	{
		DEFINE_MEMBER_N(char, name[16], 0x44);
		DEFINE_MEMBER_N(int, point, 0xD8);
		DEFINE_MEMBER_N(int, kill, 0xDC);
		DEFINE_MEMBER_N(int, killDisplay, 0xF0);
	};
};

class entPlayerInfo
{
public:
	union
	{
		DEFINE_MEMBER_N(Vector3, coords, 0x28);
		DEFINE_MEMBER_N(Vector3, velocity, 0x34);
		DEFINE_MEMBER_N(Vector2, cameraReadOnly, 0x1F8);
		DEFINE_MEMBER_N(int, weaponList[8], 0x428);
	};
};

class ent
{
public:
	union
	{
		EntPlayer* entPlayerPtr;
		DEFINE_MEMBER_N(entPlayerStat*, entPlayerStatPtr, 0x8);
		DEFINE_MEMBER_N(entPlayerInfo*, entPlayerInfoPtr, 0x10);
	};
};