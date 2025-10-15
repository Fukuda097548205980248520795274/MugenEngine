#include "InputStanceKey.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="key"></param>
void InputStanceKey::Initialize(BYTE key, float stanceWalkSpeed)
{
	// 引数を受け取る
	stanceMoveSpeed_ = stanceWalkSpeed;
	key_ = key;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// 構える
/// </summary>
bool InputStanceKey::IsStance()
{
	// ボタンを押したら構える
	if (engine_->GetKeyPress(key_))
	{
		return true;
	}

	return false;
}
