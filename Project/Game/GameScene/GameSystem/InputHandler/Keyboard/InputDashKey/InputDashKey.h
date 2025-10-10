#pragma once
#include "MugenEngine.h"

class InputDashKey
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine, BYTE key, float dashSpeed, float walkSpeed);

	/// <summary>
	/// 移動速度のGetter
	/// </summary>
	/// <returns></returns>
	float GetMoveSpeed();


private:


	/// <summary>
	/// ダッシュキーが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsPushDushKey()const { return engine_->GetKeyPress(key_); }


	// エンジン
	const MugenEngine* engine_ = nullptr;

	// ダッシュ速度
	float dashSpeed_ = 0.0f;

	// 歩き速度
	float walkSpeed_ = 0.0f;

	// ボタン
	BYTE key_;
};

