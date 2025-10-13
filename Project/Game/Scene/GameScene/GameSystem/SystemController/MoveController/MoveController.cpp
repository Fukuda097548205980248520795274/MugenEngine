#include "MoveController.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void MoveController::Initialize()
{
	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();


	// 移動操作キーの生成と初期化
	inputMoveKey_ = std::make_unique<InputMoveKey>();
	inputMoveKey_->Initialize(DIK_W, DIK_A, DIK_S, DIK_D);

	// 移動操作ゲームパッドの生成と初期化
	inputMoveGamepad_ = std::make_unique<InputMoveGamepad>();
	inputMoveGamepad_->Initialize();


	// ダッシュ操作キーの生成と初期化
	inputDashKey_ = std::make_unique<InputDashKey>();
	inputDashKey_->Initialize(DIK_SPACE, dashSpeed_, walkSpeed_);

	// ダッシュ操作ゲームパッドの生成と初期化
	inputDashGamepad_ = std::make_unique<InputDashGamepad>();
	inputDashGamepad_->Initialize(XINPUT_GAMEPAD_A, dashSpeed_, walkSpeed_);


	// 移動ロジックの生成と初期化
	logicMove_ = std::make_unique<LogicMove>();
	logicMove_->Initialize(0.1f);

	// 移動速度ロジックの生成と初期化
	logicMoveSpeed_ = std::make_unique<LogicMoveSpeed>();
	logicMoveSpeed_->Initialize(0.0f);
}

/// <summary>
/// 移動の値を取得する
/// </summary>
/// <returns></returns>
Vector3 MoveController::GetMoveValue()
{
	// 方向ベクトル
	Vector3 directionVector = Vector3(0.0f, 0.0f, 0.0f);

	// 最大速度
	float maxSpeed = 0.0f;


	// ゲームパッドが有効
	if (engine_->IsGamepadEnable(0))
	{
		// 移動方向と移動速度を取得する
		directionVector = inputMoveGamepad_->GetMoveDirection();
		maxSpeed = inputDashGamepad_->GetMoveSpeed();
	} 
	else
	{
		// ゲームパッドが無効

		// 移動方向と移動速度を取得する
		directionVector = inputMoveKey_->GetMoveDirection();
		maxSpeed = inputDashKey_->GetMoveSpeed();
	}

	// 移動ベクトルを取得する
	Vector3 moveVector = logicMove_->GetMoveVelocity(directionVector);

	// 速度ベクトルを取得する
	logicMoveSpeed_->SetMaxSpeed(maxSpeed);
	Vector3 speedVector = logicMoveSpeed_->GetSpeedVector(moveVector);

	return speedVector;
}