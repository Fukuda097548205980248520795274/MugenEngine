#pragma once
#include "MugenEngine.h"

#include "../../InputHandler/Gamepad/InputMoveGamepad/InputMoveGamepad.h"
#include "../../InputHandler/Gamepad/InputDashGamepad/InputDashGamepad.h"
#include "../../InputHandler/Gamepad/InputStanceGamepad/InputStanceGamepad.h"

#include "../../InputHandler/Keyboard/InputMoveKey/InputMoveKey.h"
#include "../../InputHandler/Keyboard/InputDashKey/InputDashKey.h"
#include "../../InputHandler/Keyboard/InputStanceKey/InputStanceKey.h"

#include "../../SystemLogic/LogicMove/LogicMove.h"
#include "../../SystemLogic/LogicMoveSpeed/LogicMoveSpeed.h"


class MoveController
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize();

	/// <summary>
	/// 移動の値を取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveValue(const Vector3& toCharacter);

	/// <summary>
	/// 現在の向いている向きを取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetCurrentDirection()const { return currentDirection_; }

	/// <summary>
	/// 構えフラグのGetter
	/// </summary>
	/// <returns></returns>
	bool IsStance()const { return isStance_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	/// <summary>
	/// キーボードで移動の値を取得する
	/// </summary>
	Vector3 GetMoveValueKeyboard(const Vector3& toCharacter);

	/// <summary>
	/// ゲームパッドで移動の値を取得する
	/// </summary>
	Vector3 GetMoveValueGamepad(const Vector3& toCharacter);



	// 今の向き
	Vector3 currentDirection_ = Vector3(0.0f, 0.0f, 0.0f);


	// 移動操作　キー
	std::unique_ptr<InputMoveKey> inputMoveKey_ = nullptr;

	// 移動操作　ゲームパッド
	std::unique_ptr<InputMoveGamepad> inputMoveGamepad_ = nullptr;

	// 歩き速度
	float walkSpeed_ = 3.0f;



	// ダッシュ操作　キー
	std::unique_ptr<InputDashKey> inputDashKey_ = nullptr;

	// ダッシュ操作　ゲームパッド
	std::unique_ptr<InputDashGamepad> inputDashGamepad_ = nullptr;

	// 走り速度
	float dashSpeed_ = 10.4f;


	// 構え操作　キー
	std::unique_ptr<InputStanceKey> inputStanceKey_ = nullptr;

	// 構え操作　ゲームパッド
	std::unique_ptr<InputStanceGamepad> inputStanceGamepad_ = nullptr;

	// 構え移動の速度
	float stanceMoveSpeed_ = 2.5f;


	// 構えフラグ
	bool isStance_ = false;


	// 移動ロジック
	std::unique_ptr<LogicMove> logicMove_ = nullptr;

	// 移動速度ロジック
	std::unique_ptr<LogicMoveSpeed> logicMoveSpeed_ = nullptr;
};

