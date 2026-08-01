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

float GetLengthSquared(const Vector3& v)
{
	const float result = (v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z);
	return result;
}

float GetLength(const Vector3& v)
{
	const float lengthSquared = GetLengthSquared(v);
	const float result = std::sqrtf(lengthSquared);
	return result;
}


bool IsNearZero(const Vector3& v)
{
	constexpr float EPSILON = 1e-8f;

	const float result = std::fabs(v.X) < EPSILON
		and std::fabs(v.Y) < EPSILON
		and std::fabs(v.Z) < EPSILON;

	return result;
}

Vector3 ReflectVector(const Vector3& v, const Vector3& normal)
{
	const Vector3 result = v - 2.0f * DotProduct(v, normal) * normal;
	return result;
}

Vector3 RefractVector(const Vector3& v, const Vector3& normal, const float etaIn, const float etaOut)
{
	const Vector3 outParallelRay = (etaIn / etaOut) * (v - normal * DotProduct(v, normal));
	const float outParallelRayLengthSqaured = min(GetLengthSquared(outParallelRay), 1.0f);
	const Vector3 outPerpendicularRay = -sqrtf(1.0f - outParallelRayLengthSqaured) * normal;
	const Vector3 result = outParallelRay + outPerpendicularRay;

	return result;
}

float RandRange(const float min, const float max)
{
	const float randFloat = float(std::rand()) / RAND_MAX;
	const float result = Lerp(min, max, randFloat);
	return result;
}

Vector3 GetRandomUnitVector()
{
	constexpr float EPSILON_LENGTH_SQUARED = 1e-8f;

	while (true)
	{
		Vector3 result =
		{
			.X = RandRange(-1.0f, 1.0f),
			.Y = RandRange(-1.0f, 1.0f),
			.Z = RandRange(-1.0f, 1.0f),
		};

		const float lengthSquared = GetLengthSquared(result);
		if (EPSILON_LENGTH_SQUARED <= lengthSquared and lengthSquared <= 1.0f)
		{
			result /= sqrtf(lengthSquared);
			return result;
		}
	}
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