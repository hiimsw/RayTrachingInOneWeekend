#pragma once

/*
* ======================================
* Vector3 Declaration
* ======================================
*/

/* Note:
* 연산자 오버로딩 규칙:
* in-place 연산자이면 멤버 함수로 구현한다. ex) [], +=, *=
* 그 외에 연산자는 전역 함수로 구현한다.
* 이유: 모든 연산자 멤버 함수로 오버로딩할 수 없을 뿐더러, 일관성이 무너질 수 있다. ex) cross, dot 함수 등
*/
struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(const float rhs);
	Vector3& operator/=(const float rhs);
};
static_assert(std::is_trivial<Vector3>::value and std::is_standard_layout<Vector3>::value, "Vector3는 POD가 유지되어야 합니다.");

/*
* ======================================
* Math Declaration
* ======================================
*/
[[nodiscard]] constexpr Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] constexpr Vector3 operator+(const Vector3& lhs, const float rhs);
[[nodiscard]] constexpr Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] constexpr Vector3 operator-(const Vector3& lhs, const float rhs);
[[nodiscard]] constexpr Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] constexpr Vector3 operator*(const Vector3& lhs, const float rhs);
[[nodiscard]] constexpr Vector3 operator*(const float lhs, const Vector3& rhs);
[[nodiscard]] constexpr Vector3 operator/(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] constexpr Vector3 operator/(const Vector3& lhs, const float rhs);

[[nodiscard]] Vector3 Normalize(const Vector3& v);
[[nodiscard]] float DotProduct(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] Vector3 CrossProduct(const Vector3& lhs, const Vector3& rhs);
[[nodiscard]] float GetLength(const Vector3& v);
[[nodiscard]] constexpr float Lerp(const float a, const float b, const float t);
[[nodiscard]] constexpr Vector3 Lerp(const Vector3& a, const Vector3& b, const float t);

/*
* ======================================
* Point Declaration
* ======================================
*/

using Point3 = Vector3;

/*
* ======================================
* Color Declaration
* ======================================
*/

using Color = Vector3;

/*
* ======================================
* Ray
* ======================================
*/

struct Ray
{
	Point3 Origin;
	Vector3 Direction;
};
static_assert(std::is_trivial<Ray>::value and std::is_standard_layout<Ray>::value, "Ray는 POD가 유지되어야 합니다.");

Vector3 GetPointOnRay(const Ray& ray, const float t);

/*
* ======================================
* Math Definition
* ======================================
*/

constexpr Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	const Vector3 result =
	{
		.X = lhs.X + rhs.X,
		.Y = lhs.Y + rhs.Y,
		.Z = lhs.Z + rhs.Z,
	};

	return result;
}

constexpr Vector3 operator+(const Vector3& lhs, const float rhs)
{
	const Vector3 result =
	{
		.X = lhs.X + rhs,
		.Y = lhs.Y + rhs,
		.Z = lhs.Z + rhs,
	};

	return result;
}

constexpr Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	const Vector3 result =
	{
		.X = lhs.X - rhs.X,
		.Y = lhs.Y - rhs.Y,
		.Z = lhs.Z - rhs.Z,
	};

	return result;
}

inline constexpr Vector3 operator-(const Vector3& lhs, const float rhs)
{
	const Vector3 result =
	{
		.X = lhs.X - rhs,
		.Y = lhs.Y - rhs,
		.Z = lhs.Z - rhs,
	};

	return result;
}

constexpr Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
{
	const Vector3 result =
	{
		.X = lhs.X * rhs.X,
		.Y = lhs.Y * rhs.Y,
		.Z = lhs.Z * rhs.Z,
	};

	return result;
}

constexpr Vector3 operator*(const Vector3& lhs, const float rhs)
{
	const Vector3 result =
	{
		.X = lhs.X * rhs,
		.Y = lhs.Y * rhs,
		.Z = lhs.Z * rhs,
	};

	return result;
}

constexpr Vector3 operator*(const float lhs, const Vector3& rhs)
{
	const Vector3 result = rhs * lhs;
	return result;
}

constexpr Vector3 operator/(const Vector3& lhs, const float rhs)
{
	const Vector3 result =
	{
		.X = lhs.X / rhs,
		.Y = lhs.Y / rhs,
		.Z = lhs.Z / rhs,
	};

	return result;
}

constexpr Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
{
	const Vector3 result =
	{
		.X = lhs.X / rhs.X,
		.Y = lhs.Y / rhs.Y,
		.Z = lhs.Z / rhs.Z,
	};

	return result;
}

constexpr float Lerp(const float a, const float b, const float t)
{
	const float result = a + (b - a) * t;
	return result;
}

constexpr Vector3 Lerp(const Vector3& a, const Vector3& b, const float t)
{
	const Vector3 result = a + (b - a) * t;
	return result;
}