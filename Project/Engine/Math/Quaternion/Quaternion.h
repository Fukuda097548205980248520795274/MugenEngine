#pragma once
#include "Math/Vector3/Vector3.h"

// クォータニオン
struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
};

namespace
{
	// 加算
	Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
	{
		// 加算
		Quaternion add;
		add.x = q1.x + q2.x;
		add.y = q1.y + q2.y;
		add.z = q1.z + q2.z;
		add.w = q1.w + q2.w;

		return add;
	}

	// 減算
	Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
	{
		// 減算
		Quaternion subtract;
		subtract.x = q1.x - q2.x;
		subtract.y = q1.y - q2.y;
		subtract.z = q1.z - q2.z;
		subtract.w = q1.w - q2.w;

		return subtract;
	}

	// スカラー倍
	Quaternion operator*(const Quaternion& quaternion, float scalar)
	{
		// スカラー倍
		Quaternion multiply;
		multiply.x = quaternion.x * scalar;
		multiply.y = quaternion.y * scalar;
		multiply.z = quaternion.z * scalar;
		multiply.w = quaternion.w * scalar;
		return multiply;
	}

	// スカラー倍
	Quaternion operator*(float scalar, const Quaternion& quaternion)
	{
		// スカラー倍
		Quaternion multiply;
		multiply.x = scalar * quaternion.x;
		multiply.y = scalar * quaternion.y;
		multiply.z = scalar * quaternion.z;
		multiply.w = scalar * quaternion.w;
		return multiply;
	}

	// スカラー除算
	Quaternion operator/(const Quaternion& quaternion, float scalar)
	{
		// スカラー除算
		Quaternion division;
		division.x = quaternion.x / scalar;
		division.y = quaternion.y / scalar;
		division.z = quaternion.z / scalar;
		division.w = quaternion.w / scalar;
		return division;
	}

	// スカラー除算
	Quaternion operator/(float scalar, const Quaternion& quaternion)
	{
		// スカラー除算
		Quaternion division;
		division.x = scalar / quaternion.x;
		division.y = scalar / quaternion.y;
		division.z = scalar / quaternion.z;
		division.w = scalar / quaternion.w;
		return division;
	}

	// 積
	Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
	{
		// ベクトルに変換する
		Vector3 v1 = Vector3(q1.x, q1.y, q1.z);
		Vector3 v2 = Vector3(q2.x, q2.y, q2.z);

		// ベクトル部の積
		Vector3 vecMultiply = Cross(v1, v2) + q2.w * v1 + q1.w * v2;

		// 積
		Quaternion multiply;
		multiply.x = vecMultiply.x;
		multiply.y = vecMultiply.y;
		multiply.z = vecMultiply.z;
		multiply.w = q1.w * q2.w - Dot(v1, v2);

		return multiply;
	}

	// +
	Quaternion operator+(const Quaternion& quaternion)
	{
		return quaternion;
	}

	// -
	Quaternion operator-(const Quaternion& quaternion)
	{
		Quaternion minus = Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, -quaternion.w);
		return minus;
	}
}

/// <summary>
/// 乗法単位元を求める
/// </summary>
/// <returns></returns>
Quaternion MakeIdentityQuaternion();

/// <summary>
/// 共役クォータニオンを作成する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion MakeConjugateQuaternion(const Quaternion& quaternion);

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
float Length(const Quaternion& quaternion);

/// <summary>
/// 正規化する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion Normalize(const Quaternion& quaternion);

/// <summary>
/// 逆クォータニオンを作成する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion MakeInverseQuaternion(const Quaternion& quaternion);