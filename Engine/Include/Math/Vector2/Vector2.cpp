#include "Vector2.h"

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
float Length(const Vector2& vector)
{
	// 長さ
	float length = std::sqrtf(std::powf(vector.x, 2.0f) + std::powf(vector.y, 2.0f));
	return length;
}

/// <summary>
/// 正規化する
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns></returns>
Vector2 Normalize(const Vector2& vector)
{
	// 長さ
	float length = Length(vector);

	// 正規化したベクトル
	Vector2 normalizeVector = Vector2(0.0f, 0.0f);

	// 長さがあるとき、処理する
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
Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
{
	return (1.0f - t) * start + t * end;
}

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Dot(const Vector2& v1, const Vector2& v2)
{
	float dot = v1.x * v2.x + v1.y * v2.y;
	return dot;
}

/// <summary>
/// クロス積を求める
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
float Cross(const Vector2& v1, const Vector2& v2)
{
	float cross = v1.x * v2.y - v1.y * v2.x;
	return cross;
}

/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="point"></param>
/// <param name="vector"></param>
/// <returns></returns>
Vector2 Project(const Vector2& point, const Vector2& vector)
{
	// ベクトルを正規化する
	Vector2 normalize = Normalize(vector);

	Vector2 project = Dot(point, normalize) * normalize;
	return project;
}