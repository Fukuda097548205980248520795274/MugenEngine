#pragma once
#include "MugenEngine.h"

class InputMoveKey
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="front"></param>
	/// <param name="left"></param>
	/// <param name="back"></param>
	/// <param name="right"></param>
	void Initialize(const MugenEngine* engine, BYTE front, BYTE left, BYTE back, BYTE right);

	/// <summary>
	/// 押したキーに合わせて方向ベクトルを求める
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveDirection();


private:

	/// <summary>
	/// 奥移動ボタンが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsFront()const { return engine_->GetKeyPress(front_); }

	/// <summary>
	/// 左移動ボタンが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsLeft()const { return engine_->GetKeyPress(left_); }

	/// <summary>
	/// 手前移動ボタンが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsBack()const { return engine_->GetKeyPress(back_); }

	/// <summary>
	/// 右移動ボタンが押されたかどうか
	/// </summary>
	/// <returns></returns>
	bool IsRight()const { return engine_->GetKeyPress(right_); }



	// エンジン
	const MugenEngine* engine_ = nullptr;


	// 奥
	BYTE front_;

	// 左
	BYTE left_;

	// 手前
	BYTE back_;

	// 右
	BYTE right_;
};

