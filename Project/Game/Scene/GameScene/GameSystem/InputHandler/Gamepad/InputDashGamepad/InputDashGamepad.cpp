#include "InputDashGamepad.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputDashGamepad::Initialize(const MugenEngine* engine, DWORD button, float dashSpeed, float walkSpeed)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	button_ = button;
	dashSpeed_ = dashSpeed;
	walkSpeed_ = walkSpeed;
}

/// <summary>
/// 最大ダッシュ速度のGetter
/// </summary>
/// <returns></returns>
float InputDashGamepad::GetMoveSpeed()
{
	// ダッシュボタンが押されたら、ダッシュ速度を返却する
	if (IsPushDushButton())
	{
		return dashSpeed_;
	}

	// 押されなかったら歩き速度を返却する
	return walkSpeed_;
}