#pragma once
#include "MugenEngine.h"

#include "../../InputHandler/Gamepad/InputMoveGamepad/InputMoveGamepad.h"
#include "../../InputHandler/Gamepad/InputDashGamepad/InputDashGamepad.h"
#include "../../InputHandler/Keyboard/InputMoveKey/InputMoveKey.h"
#include "../../InputHandler/Keyboard/InputDashKey/InputDashKey.h"
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
	Vector3 GetMoveValue();


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;



	// 移動操作　キー
	std::unique_ptr<InputMoveKey> inputMoveKey_ = nullptr;

	// 移動操作　ゲームパッド
	std::unique_ptr<InputMoveGamepad> inputMoveGamepad_ = nullptr;

	// 歩き速度
	float walkSpeed_ = 0.035f;



	// ダッシュ操作　キー
	std::unique_ptr<InputDashKey> inputDashKey_ = nullptr;

	// ダッシュ操作　ゲームパッド
	std::unique_ptr<InputDashGamepad> inputDashGamepad_ = nullptr;

	// 走り速度
	float dashSpeed_ = 0.125f;



	// 移動ロジック
	std::unique_ptr<LogicMove> logicMove_ = nullptr;

	// 移動速度ロジック
	std::unique_ptr<LogicMoveSpeed> logicMoveSpeed_ = nullptr;
};

