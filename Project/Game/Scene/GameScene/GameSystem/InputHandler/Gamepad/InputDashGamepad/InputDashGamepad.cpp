#include "InputDashGamepad.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputDashGamepad::Initialize(DWORD button, float dashSpeed, float walkSpeed)
{
	// 引数を受け取る
	button_ = button;
	dashSpeed_ = dashSpeed;
	walkSpeed_ = walkSpeed;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
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