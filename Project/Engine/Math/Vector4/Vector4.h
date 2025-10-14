#pragma once
#include <cmath>

// 4次元ベクトル
struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

/// <summary>
/// 線形補間を行う
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector4 Lerp(const Vector4& start, const Vector4& end, float t);