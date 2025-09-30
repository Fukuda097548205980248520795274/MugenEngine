#pragma once
#include <cmath>

// 二次元ベクトル
struct Vector2
{
	float x;
	float y;

	// 加算
	Vector2 operator+=(const Vector2& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		return *this;
	}

	// 減算
	Vector2 operator-=(const Vector2& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		return *this;
	}

	// スカラー倍
	Vector2 operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	// スカラー除算
	Vector2 operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}
};

namespace
{
	// 加算
	Vector2 operator+(const Vector2& v1, const Vector2& v2)
	{
		// 加算
		Vector2 add;
		add.x = v1.x + v2.x;
		add.y = v1.y + v2.y;
		return add;
	}

	// 減算
	Vector2 operator-(const Vector2& v1, const Vector2& v2)
	{
		// 減算
		Vector2 subtract;
		subtract.x = v1.x - v2.x;
		subtract.y = v1.y - v2.y;
		return subtract;
	}

	// スカラー倍
	Vector2 operator*(const Vector2& vector, float scalar)
	{
		// 乗算
		Vector2 multiply;
		multiply.x = vector.x * scalar;
		multiply.y = vector.y * scalar;
		return multiply;
	}

	// スカラー倍
	Vector2 operator*(float scalar,const Vector2& vector)
	{
		// 乗算
		Vector2 multiply;
		multiply.x = scalar * vector.x;
		multiply.y = scalar * vector.y;
		return multiply;
	}

	// スカラー除算
	Vector2 operator/(const Vector2& vector, float scalar)
	{
		// 乗算
		Vector2 division;
		division.x = vector.x / scalar;
		division.y = vector.y / scalar;
		return division;
	}

	// スカラー除算
	Vector2 operator/(float scalar, const Vector2& vector)
	{
		// 乗算
		Vector2 division;
		division.x = scalar / vector.x;
		division.y = scalar / vector.y;
		return division;
	}

	// +
	Vector2 operator+(const Vector2& vector)
	{
		return vector;
	}

	// -
	Vector2 operator-(const Vector2& vector)
	{
		return Vector2(-vector.x, -vector.y);
	}
}

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
float Length(const Vector2& vector);

/// <summary>
/// 正規化する
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
Vector2 Normalize(const Vector2& vector);

/// <summary>
/// 線形補間を求める
/// </summary>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="t">倍か変数</param>
/// <returns></returns>
Vector2 Lerp(const Vector2& start, const Vector2& end, float t);

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Dot(const Vector2& v1, const Vector2& v2);

/// <summary>
/// クロス積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Cross(const Vector2& v1, const Vector2& v2);

/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="point"></param>
/// <param name="vector"></param>
/// <returns></returns>
Vector2 Project(const Vector2& point, const Vector2& vector);

/// <summary>
/// 反射ベクトルを求める
/// </summary>
/// <param name="input">入射ベクトル</param>
/// <param name="normal">法線</param>
/// <returns></returns>
Vector2 Reflect(const Vector2& input, const Vector2& normal);