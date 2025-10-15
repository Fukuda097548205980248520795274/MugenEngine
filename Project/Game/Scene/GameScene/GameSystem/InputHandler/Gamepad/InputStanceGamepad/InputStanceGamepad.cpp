#include "InputStanceGamepad.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="button"></param>
void InputStanceGamepad::Initialize(DWORD button, float stanceWalkSpeed)
{
	// 引数を受け取る
	stanceMoveSpeed_ = stanceWalkSpeed;
	button_ = button;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// 構える
/// </summary>
bool InputStanceGamepad::IsStance()
{
	// ゲームコントローラが有効かどうか
	if (!engine_->IsGamepadEnable(0))
		return false;

	// ボタンを押したら構える
	if (engine_->GetGamepadButtonPress(0, button_))
	{
		return true;
	}

	return false;
}
