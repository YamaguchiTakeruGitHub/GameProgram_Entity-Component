#pragma once

struct Vector3
{
	float x, y, z;
};

Vector3 VecGet(const float& x, const float& y, const float& z);

Vector3 VecAdd(const Vector3& v1, const Vector3& v2);

Vector3 VecSub(const Vector3& v1, const Vector3& v2);

float VecSize(const Vector3& v);

Vector3 VecNorm(const Vector3& v);

Vector3 VecScale(const Vector3& v, const float& scale);