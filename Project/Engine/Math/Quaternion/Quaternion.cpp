#include "Quaternion.h"

/// <summary>
/// 乗法単位元を求める
/// </summary>
/// <returns></returns>
Quaternion MakeIdentityQuaternion()
{
	Quaternion quaternion;

	quaternion.x = 0.0f;
	quaternion.y = 0.0f;
	quaternion.z = 0.0f;
	quaternion.w = 1.0f;

	return quaternion;
}

/// <summary>
/// 共役クォータニオンを作成する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion MakeConjugateQuaternion(const Quaternion& quaternion)
{
	Quaternion conjugate;

	conjugate.x = -quaternion.x;
	conjugate.y = -quaternion.y;
	conjugate.z = -quaternion.z;
	conjugate.w = quaternion.w;

	return conjugate;
}

/// <summary>
/// 長さを求める
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
float Length(const Quaternion& quaternion)
{
	float length =
		std::sqrtf(std::powf(quaternion.w, 2.0f) + std::powf(quaternion.x, 2.0f) + std::powf(quaternion.y, 2.0f) + std::powf(quaternion.z, 2.0f));

	return length;
}

/// <summary>
/// 正規化する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion Normalize(const Quaternion& quaternion)
{
	// 長さ
	float length = Length(quaternion);

	// 正規化した値
	Quaternion normalize = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	if (length != 0.0f)
	{
		normalize = quaternion / length;
	}

	return normalize;
}

/// <summary>
/// 逆クォータニオンを作成する
/// </summary>
/// <param name="quaternion"></param>
/// <returns></returns>
Quaternion MakeInverseQuaternion(const Quaternion& quaternion)
{
	return MakeConjugateQuaternion(quaternion) / std::powf(Length(quaternion), 2.0f);
}