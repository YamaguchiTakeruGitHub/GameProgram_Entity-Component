#include "Vector3.h"
#include <cmath>

Vector3 VecGet(const float& x, const float& y, const float& z)
{
	return Vector3{ x, y, z };
}

Vector3 VecAdd(const Vector3& v1, const Vector3& v2)
{
	return Vector3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 VecSub(const Vector3& v1, const Vector3& v2)
{
	return Vector3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

float VecSize(const Vector3& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 VecNorm(const Vector3& v)
{
	float size = VecSize(v);
	if (size == 0.0f) return { 0, 0, 0 };
	return { v.x / size, v.y / size, v.z / size };
}

Vector3 VecScale(const Vector3& v, const float& scale)
{
	return Vector3{ v.x * scale, v.y * scale, v.z * scale };
}

