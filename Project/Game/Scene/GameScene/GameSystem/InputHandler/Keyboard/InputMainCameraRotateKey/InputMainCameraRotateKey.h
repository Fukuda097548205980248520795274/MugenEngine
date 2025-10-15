#pragma once
#include "MugenEngine.h"

class InputMainCameraRotateKey
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="upKey"></param>
	/// <param name="leftKey"></param>
	/// <param name="downKey"></param>
	/// <param name="rightKey"></param>
	/// <param name="rotateSpeed"></param>
	void Initialize(BYTE upKey, BYTE leftKey, BYTE downKey, BYTE rightKey, float rotateSpeed);

	/// <summary>
	/// 回転の方向を取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetRotateDirection();

	/// <summary>
	/// 回転速度のGetter
	/// </summary>
	/// <returns></returns>
	float GetRotateSpeed()const { return rotateSpeed_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;


	/// <summary>
	/// 上キーを押したかどうか
	/// </summary>
	/// <returns></returns>
	bool IsUp()const { return engine_->GetKeyPress(upKey_); }

	/// <summary>
	/// 左キーを押したかどうか
	/// </summary>
	/// <returns></returns>
	bool IsLeft()const { return engine_->GetKeyPress(leftKey_); }

	/// <summary>
	/// 下キーを押したかどうか
	/// </summary>
	/// <returns></returns>
	bool IsDown()const { return engine_->GetKeyPress(downKey_); }

	/// <summary>
	/// 右キーを押したかどうか
	/// </summary>
	/// <returns></returns>
	bool IsRight()const { return engine_->GetKeyPress(rightKey_); }


	// 上キー
	BYTE upKey_;

	// 左キー
	BYTE leftKey_;

	// 下キー
	BYTE downKey_;

	// 右キー
	BYTE rightKey_;

	
	// 回転速度
	float rotateSpeed_ = 0.0f;
};

