#include "pch.h"
#include "Util.h"

/*
* ======================================
* Vector3
* ======================================
*/

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;

	return *this;
}

Vector3& Vector3::operator*=(const float rhs)
{
	X *= rhs;
	Y *= rhs;
	Z *= rhs;

	return *this;
}

Vector3& Vector3::operator/=(const float rhs)
{
	X /= rhs;
	Y /= rhs;
	Z /= rhs;

	return *this;
}

Vector3 Normalize(const Vector3& v)
{
	const float length = GetLength(v);
	const Vector3 result =
	{
		v.X / length,
		v.Y / length,
		v.Z / length
	};

	return result;
}

float DotProduct(const Vector3& lhs, const Vector3& rhs)
{
	const float result = lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
	return result;
}

Vector3 CrossProduct(const Vector3& lhs, const Vector3& rhs)
{
	const Vector3 result
	{
		.X = lhs.Y * rhs.Z - lhs.Z * rhs.Y,
		.Y = lhs.Z * rhs.X - lhs.X * rhs.Z,
		.Z = lhs.X * rhs.Y - lhs.Y * rhs.X
	};
	return result;
}

float GetLength(const Vector3& v)
{
	const float result = std::sqrtf((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z));
	return result;
}

/*
* ======================================
* Ray
* ======================================
*/

Point3 GetPointOnRay(const Ray& ray, const float t)
{
	const Point3 point = ray.Origin + (ray.Direction * t);
	return point;
}

/*
* ======================================
* Random Definition
* ======================================
*/


float RandRange(const float min, const float max)
{
	const float randFloat = float(std::rand()) / RAND_MAX;
	const float result = Lerp(min, max, randFloat);
	return result;
}
