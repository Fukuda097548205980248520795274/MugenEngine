#pragma once
#include "MugenEngine.h"

class InputStanceKey
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="key"></param>
	void Initialize(BYTE key, float stanceWalkSpeed);

	/// <summary>
	/// 構える
	/// </summary>
	bool IsStance();

	/// <summary>
	/// 構え移動の速度を取得する
	/// </summary>
	/// <returns></returns>
	float GetStanceMoveSpeed()const { return stanceMoveSpeed_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;



	// キー
	BYTE key_;

	// 構え移動の速度
	float stanceMoveSpeed_ = 0.0f;
};

