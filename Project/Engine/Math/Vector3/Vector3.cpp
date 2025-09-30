#include "Vector3.h"

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
float Length(const Vector3& vector)
{
	// 長さ
	float length = std::sqrtf(std::powf(vector.x, 2.0f) + std::powf(vector.y, 2.0f) + std::powf(vector.z, 2.0f));
	return length;
}

/// <summary>
/// 正規化する
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Normalize(const Vector3& vector)
{
	// 長さ
	float length = Length(vector);

	// 正規化したベクトル
	Vector3 normalizeVector = Vector3(0.0f, 0.0f, 0.0f);

	// 長さがあるときのみ処理する
	if (length != 0.0f)
	{
		normalizeVector = vector / length;
	}

	return normalizeVector;
}

/// <summary>
/// 線形補間を求める
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector3 Lerp(const Vector3& start, const Vector3& end, float t)
{
	return (1.0f - t) * start + t * end;
}

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Dot(const Vector3& v1, const Vector3& v2)
{
	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return dot;
}

/// <summary>
/// クロス積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 cross;
	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return cross;
}

/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="point"></param>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Project(const Vector3& point, const Vector3& vector)
{
	// ベクトルを正規化する
	Vector3 normalize = Normalize(vector);

	Vector3 project = Dot(point, normalize) * normalize;
	return project;
}

/// <summary>
/// 反射ベクトルを求める
/// </summary>
/// <param name="input">入射ベクトル</param>
/// <param name="normal">法線</param>
/// <returns></returns>
Vector3 Reflect(const Vector3& input, const Vector3& normal)
{
	Vector3 reflect = input - (2.0f * (Dot(input, normal) * normal));
	return reflect;
}