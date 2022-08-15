#pragma once

#include "SDK.h"

struct Variables
{
	uintptr_t* gCli = (uintptr_t*)(SDK::t6zm + SDK::gClient);
	uintptr_t* gCliStat = (uintptr_t*)(SDK::t6zm + SDK::gClient + SDK::gClientStat);
	uintptr_t* gCliInfo = (uintptr_t*)(SDK::t6zm + SDK::gClient + SDK::gClientInfo);

	uintptr_t* baseZombEntList = (uintptr_t*)(SDK::t6zm + SDK::zombieEntList);

	bool godMode = false;
	bool point = false;
	bool tpZombie = false;
}var;

class Vector2
{
public:
	float x, y;

	Vector2() {};
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }
	Vector2& operator += (const Vector2& rhs) { return *this = *this + rhs; }
	Vector2& operator -= (const Vector2& rhs) { return *this = *this - rhs; }
	Vector2& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector2& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y); }
	Vector2 Normalize() const { return *this * (1 / Length()); }
};

using Vec2 = Vector2;
using vec2 = Vector2;

class Vector3
{
public:

	float x, y, z;

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
};

using Vec3 = Vector3;
using vec3 = Vector3;

double ConvertToRadians(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}