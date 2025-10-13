#include "BaseCharacter.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="startPosition"></param>
void BaseCharacter::Initialize(const Camera3D* camera3d, const Vector3& startPosition)
{
	// nullptrチェック
	assert(camera3d);
	
	// 引数を受け取る
	camera3d_ = camera3d;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform3D>();
	worldTransform_->Initialize();
	worldTransform_->translation_ = startPosition;
}

/// <summary>
/// 更新処理
/// </summary>
void BaseCharacter::Update()
{
	// ワールドトランスフォームの更新処理
	worldTransform_->Update();
}