#pragma once
#include "MugenEngine.h"

class InputDashGamepad
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(DWORD button, float dashSpeed, float walkSpeed);

	/// <summary>
	/// 移動速度のGetter
	/// </summary>
	/// <returns></returns>
	float GetMoveSpeed();


private:


	/// <summary>
	/// ダッシュボタンが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsPushDushButton()const { return engine_->GetGamepadButtonPress(0, button_); }


	// エンジン
	const MugenEngine* engine_ = nullptr;

	// ダッシュ速度
	float dashSpeed_ = 0.0f;

	// 歩き速度
	float walkSpeed_ = 0.0f;

	// ボタン
	DWORD button_;
};

