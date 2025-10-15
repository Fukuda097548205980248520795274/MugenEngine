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


	// 構え操作キーの生成と初期化
	inputStanceKey_ = std::make_unique<InputStanceKey>();
	inputStanceKey_->Initialize(DIK_O, stanceMoveSpeed_);

	// 構え操作ゲームパッドの生成と初期化
	inputStanceGamepad_ = std::make_unique<InputStanceGamepad>();
	inputStanceGamepad_->Initialize(XINPUT_GAMEPAD_RIGHT_SHOULDER, stanceMoveSpeed_);


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
	// ゲームパッドが有効
	if (engine_->IsGamepadEnable(0))
	{
		return GetMoveValueGamepad();
	} 
	else
	{
		// ゲームパッドが無効
		return GetMoveValueKeyboard();
	}
}


/// <summary>
/// キーボードで移動の値を取得する
/// </summary>
Vector3 MoveController::GetMoveValueKeyboard()
{
	// 方向ベクトル
	Vector3 directionVector = Vector3(0.0f, 0.0f, 0.0f);

	// 最大速度
	float maxSpeed = 0.0f;


	// 移動方向と移動速度を取得する
	directionVector = inputMoveKey_->GetMoveDirection();

	// 構えている時　構え移動
	if (inputStanceGamepad_->IsStance())
	{
		maxSpeed = inputStanceKey_->GetStanceMoveSpeed();
	}
	else
	{
		// 構えて着ないとき　移動・ダッシュ
		maxSpeed = inputDashKey_->GetMoveSpeed();
	}

	// 移動ベクトルを取得する
	Vector3 moveVector = logicMove_->GetMoveVelocity(directionVector);

	// 速度ベクトルを取得する
	logicMoveSpeed_->SetMaxSpeed(maxSpeed);
	Vector3 speedVector = logicMoveSpeed_->GetSpeedVector(moveVector);

	// 構えていないときに向きを更新する
	if (!inputStanceKey_->IsStance())
		currentDirection_ = Normalize(directionVector);

	return speedVector;
}

/// <summary>
/// ゲームパッドで移動の値を取得する
/// </summary>
Vector3 MoveController::GetMoveValueGamepad()
{
	// 方向ベクトル
	Vector3 directionVector = Vector3(0.0f, 0.0f, 0.0f);

	// 最大速度
	float maxSpeed = 0.0f;


	// 移動方向と移動速度を取得する
	directionVector = inputMoveGamepad_->GetMoveDirection();

	// 構えている時　構え移動
	if (inputStanceGamepad_->IsStance())
	{
		maxSpeed = inputStanceGamepad_->GetStanceMoveSpeed();
	}
	else
	{
		// 構えて着ないとき　移動・ダッシュ
		maxSpeed = inputDashGamepad_->GetMoveSpeed();
	}

	// 移動ベクトルを取得する
	Vector3 moveVector = logicMove_->GetMoveVelocity(directionVector);

	// 速度ベクトルを取得する
	logicMoveSpeed_->SetMaxSpeed(maxSpeed);
	Vector3 speedVector = logicMoveSpeed_->GetSpeedVector(moveVector);

	// 構えていないときに向きを更新する
	if (!inputStanceGamepad_->IsStance())
		currentDirection_ = Normalize(directionVector);

	return speedVector;
}