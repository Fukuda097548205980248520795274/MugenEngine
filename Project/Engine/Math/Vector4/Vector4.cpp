#include "Vector4.h"

/// <summary>
/// 線形補間を行う
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector4 Lerp(const Vector4& start, const Vector4& end, float t)
{
	Vector4 lerp;
	lerp.x = start.x * (1.0f - t) + end.x * t;
	lerp.y = start.y * (1.0f - t) + end.y * t;
	lerp.z = start.z * (1.0f - t) + end.z * t;
	lerp.w = start.w * (1.0f - t) + end.w * t;
	return lerp;
}