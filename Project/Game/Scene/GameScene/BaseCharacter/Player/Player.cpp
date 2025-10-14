#include "Player.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="startPosition"></param>
void Player::Initialize(const Camera3D* camera3d, const Vector3& startPosition)
{
	// 基底クラスの初期化
	BaseCharacter::Initialize(camera3d, startPosition);

	// 移動コントローラの生成と初期化
	moveController_ = std::make_unique<MoveController>();
	moveController_->Initialize();

	// モデルの生成と初期化
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(camera3d_, engine_->LoadModel("./Resources/Models/multiMaterial", "multiMaterial.obj"));
	model_->SetParent(worldTransform_.get());
	
	// UVトランスフォームを取得する
	UVTransform* planeUVTransform = model_->GetUVTransform("Plane");
	UVTransform* cubeUVTransform = model_->GetUVTransform("Cube");

	// グループ名
	std::string groupName = "Player";
	engine_->SetSettingValue(groupName, "translation", &worldTransform_->translation_);
	engine_->SetSettingValue(groupName, "uvTransform_0_rotate", &planeUVTransform->rotation_);
	engine_->SetSettingValue(groupName, "uvTransform_1_rotate", &cubeUVTransform->rotation_);
	engine_->RegistGroupDataReflection(groupName);
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{

	// 移動の値を取得して、移動する
	worldTransform_->translation_ += moveController_->GetMoveValue();
	

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
