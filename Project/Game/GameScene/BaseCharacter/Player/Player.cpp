#include "Player.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="startPosition"></param>
void Player::Initialize(const MugenEngine* engine, const Camera3D* camera3d, const Vector3& startPosition)
{
	// 基底クラスの初期化
	BaseCharacter::Initialize(engine, camera3d, startPosition);


	// 移動操作キーの生成と初期化
	inputMoveKey_ = std::make_unique<InputMoveKey>();
	inputMoveKey_->Initialize(engine_, DIK_W, DIK_A, DIK_S, DIK_D);

	// 移動操作ゲームパッドの生成と初期化
	inputMoveGamepad_ = std::make_unique<InputMoveGamepad>();
	inputMoveGamepad_->Initialize(engine_);

	// 移動ロジックの生成と初期化
	logicMove_ = std::make_unique<LogicMove>();
	logicMove_->Initialize(0.1f);

	// 移動速度ロジックの生成と初期化
	logicMoveSpeed_ = std::make_unique<LogicMoveSpeed>();
	logicMoveSpeed_->Initialize(0.035f);



	// モデルの生成と初期化
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(engine_, camera3d_, engine_->LoadModel("./Resources/Models/characterBox", "characterBox.obj"));
	model_->SetParent(worldTransform_.get());
	model_->material_->enableHalfLambert_ = true;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	// 方向ベクトル
	Vector3 directionVector = Vector3(0.0f, 0.0f, 0.0f);

	// ゲームパッドが有効
	if (engine_->IsGamepadEnable(0))
	{
		directionVector = inputMoveGamepad_->GetMoveDirection();
	}
	else
	{
		// ゲームパッドが無効
		directionVector = inputMoveKey_->GetMoveDirection();
	}

	// 移動ベクトル
	Vector3 moveVector = logicMove_->GetMoveVelocity(directionVector);

	// 速度ベクトル
	Vector3 speedVector = logicMoveSpeed_->GetSpeedVector(moveVector);


	// 移動する
	worldTransform_->translation_ += speedVector;


	// 基底クラスの更新処理
	BaseCharacter::Update();

	// モデルの更新処理
	model_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	// モデルの描画処理
	model_->Draw();
}