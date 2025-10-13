#include "InputDashKey.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputDashKey::Initialize(BYTE key, float dashSpeed, float walkSpeed)
{
	// 引数を受け取る
	key_ = key;
	dashSpeed_ = dashSpeed;
	walkSpeed_ = walkSpeed;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// 移動速度のGetter
/// </summary>
/// <returns></returns>
float InputDashKey::GetMoveSpeed()
{
	// ダッシュボタンが押されたら、ダッシュ速度を返却する
	if (IsPushDushKey())
	{
		return dashSpeed_;
	}

	// 押されていないときは歩き速度を返却する
	return walkSpeed_;
}