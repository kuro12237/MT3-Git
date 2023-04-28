#pragma once

#include<math.h>
#include<Novice.h>
#include<Default.h>

/*
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
Vector3 sbcract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;


}

float Length(const Vector3& v)
{
	float result;
	result = float(sqrt(Dot(v, v)));
	return result;

}

Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

/*
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnwidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnwidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnwidth * 3, y, "%s", label);
}

*/
