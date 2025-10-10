#include "InputDashKey.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputDashKey::Initialize(const MugenEngine* engine, BYTE key, float dashSpeed, float walkSpeed)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	key_ = key;
	dashSpeed_ = dashSpeed;
	walkSpeed_ = walkSpeed;
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