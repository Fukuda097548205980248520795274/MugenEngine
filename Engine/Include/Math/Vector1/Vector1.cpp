#include "Vector1.h"

/// <summary>
/// 線形補間を求める
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="t"></param>
/// <returns></returns>
float Lerp(float start, float end, float t)
{
	return (1.0f - t) * start + t * end;
}