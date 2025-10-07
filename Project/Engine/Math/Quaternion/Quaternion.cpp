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

/// <summary>
/// 内積を求める
/// </summary>
/// <param name="q1"></param>
/// <param name="q2"></param>
/// <returns></returns>
float Dot(const Quaternion& q1, const Quaternion& q2)
{
	float dot = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	return dot;
}

/// <summary>
/// 球面線形補間を行う
/// </summary>
/// <param name="q1"></param>
/// <param name="q2"></param>
/// <param name="t"></param>
/// <returns></returns>
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	// 片方のクォータニオンのコピー
	Quaternion q0Copy = q0;

	// 内積
	float dot = Dot(q0Copy, q1);

	// 最短経路を確保
	if (dot < 0.0f)
	{
		q0Copy = -q0Copy;
		dot = -dot;
	}

	// 許容誤差（イプシロン）を定義。例えば 1e-6f など。
	const float DOT_THRESHOLD = 1.0f - 1e-4f; // 例として 0.9999f

	// クォータニオンが非常に近い場合（thetaが非常に小さい場合）
	// 線形補間（Lerp）にフォールバックして、ゼロ除算を防ぐ
	if (dot > DOT_THRESHOLD)
	{
		// 単純な線形補間を実行（後で正規化が必要）
		Quaternion result = (1.0f - t) * q0Copy + t * q1;
		// 結果を正規化して返却
		return Normalize(result); // Normalize関数があるとして
	}

	// --- 通常の Slerp 処理 ---

	// なす角を求める
	float theta = std::acos(dot);

	// std::sin(theta) がゼロになることは、上の Lerp 処理で回避済み

	// 補間 0.0f
	float scale0 = std::sin((1.0f - t) * theta) / std::sin(theta);

	// 補間 1.0f
	float scale1 = std::sin(t * theta) / std::sin(theta);

	// 補間した値を返却する
	return scale0 * q0Copy + scale1 * q1;
}
