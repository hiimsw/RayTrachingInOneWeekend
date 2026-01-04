#pragma once

namespace Math
{
	struct Vector3
	{
		float X;
		float Y;
		float Z;
	};

	inline Vector3 AddVector(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 SubtractVector(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 ScaleVector(const Vector3& vector, const float scalar);
	inline float DotProdouct(const Vector3& lhs, const Vector3& rhs);
	inline Vector3 CrossProdouct(const Vector3& lhs, const Vector3& rhs);
	inline float GetVectorLenght(const Vector3& vector);

	Vector3 AddVector(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result
		{
			.X = lhs.X + rhs.X,
			.Y = lhs.Y + rhs.Y,
			.Z = lhs.Z + rhs.Z,
		};
		return result;
	}

	Vector3 SubtractVector(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result
		{
			.X = lhs.X - rhs.X,
			.Y = lhs.Y - rhs.Y,
			.Z = lhs.Z - rhs.Z,
		};
		return result;
	}

	Vector3 ScaleVector(const Vector3& vector, const float scalar)
	{
		Vector3 result{ .X = vector.X * scalar, .Y = vector.Y * scalar, .Z = vector.Z * scalar };
		return result;
	}

	float DotProdouct(const Vector3& lhs, const Vector3& rhs)
	{
		float result = lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
		return result;
	}

	Vector3 CrossProdouct(const Vector3& u, const Vector3& v)
	{
		Vector3 result
		{
			.X = u.Y * v.Z - u.Z * v.Y,
			.Y = u.Z * v.X - u.X * v.Z,
			.Z = u.X * v.Y - u.Y * v.X
		};
		return result;
	}

	float GetVectorLenght(const Vector3& vector)
	{
		float result = std::sqrtf((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
		return result;
	}
}