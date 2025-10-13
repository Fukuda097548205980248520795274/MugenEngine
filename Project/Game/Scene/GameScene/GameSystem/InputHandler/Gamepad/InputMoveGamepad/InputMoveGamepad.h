#pragma once
#include "MugenEngine.h"

class InputMoveGamepad
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize();

	/// <summary>
	/// スティックに合わせて方向ベクトルを求める
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveDirection();

private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// デッドゾーン
	float deadzone_ = 0.3f;
};

