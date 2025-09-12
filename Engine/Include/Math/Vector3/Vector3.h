#pragma once
#include <cmath>

// 三次元ベクトル
struct Vector3
{
	float x;
	float y;
	float z;

	// 加算
	Vector3 operator+=(const Vector3& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		this->z += vector.z;
		return *this;
	}

	// 減算
	Vector3 operator-=(const Vector3& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		this->z -= vector.z;
		return *this;
	}

	// スカラー倍
	Vector3 operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	// スカラー除算
	Vector3 operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}
};

namespace
{
	// 加算
	Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		// 加算
		Vector3 add;
		add.x = v1.x + v2.x;
		add.y = v1.y + v2.y;
		add.z = v1.z + v2.z;
		return add;
	}

	// 減算
	Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		// 減算
		Vector3 subtract;
		subtract.x = v1.x - v2.x;
		subtract.y = v1.y - v2.y;
		subtract.z = v1.z - v2.z;
		return subtract;
	}

	// スカラー倍
	Vector3 operator*(const Vector3& vector, float scalar)
	{
		// 乗算
		Vector3 multiply;
		multiply.x = vector.x * scalar;
		multiply.y = vector.y * scalar;
		multiply.z = vector.z * scalar;
		return multiply;
	}

	// スカラー倍
	Vector3 operator*(float scalar, const Vector3& vector)
	{
		// 乗算
		Vector3 multiply;
		multiply.x = scalar * vector.x;
		multiply.y = scalar * vector.y;
		multiply.z = scalar * vector.z;
		return multiply;
	}

	// スカラー除算
	Vector3 operator/(const Vector3& vector, float scalar)
	{
		// 乗算
		Vector3 division;
		division.x = vector.x / scalar;
		division.y = vector.y / scalar;
		division.z = vector.z / scalar;
		return division;
	}

	// スカラー除算
	Vector3 operator/(float scalar, const Vector3& vector)
	{
		// 乗算
		Vector3 division;
		division.x = scalar / vector.x;
		division.y = scalar / vector.y;
		division.z = scalar / vector.z;
		return division;
	}

	// +
	Vector3 operator+(const Vector3& vector)
	{
		return vector;
	}

	// -
	Vector3 operator-(const Vector3& vector)
	{
		return Vector3(-vector.x, -vector.y, -vector.z);
	}
}

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
float Length(const Vector3& vector);

/// <summary>
/// 正規化する
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Normalize(const Vector3& vector);

/// <summary>
/// 線形補間を求める
/// </summary>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="t">媒介変数</param>
/// <returns></returns>
Vector3 Lerp(const Vector3& start, const Vector3& end, float t);

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Dot(const Vector3& v1, const Vector3& v2);

/// <summary>
/// クロス積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="point"></param>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Project(const Vector3& point, const Vector3& vector);