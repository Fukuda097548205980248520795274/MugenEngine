#include "BaseMesh.h"
#include <MugenEngine.h>

/// <summary>
/// 初期化
/// </summary>
/// <param name="camera3d"></param>
/// <param name="textureHandle"></param>
void BaseMesh::Initialize(const MugenEngine* engine, const Camera3D* camera3d, TextureHandle textureHandle)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	textureHandle_ = textureHandle;

	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform3D>();
	worldTransform_->Initialize();

	// UVトランスフォームの生成と初期化
	uvTransform_ = std::make_unique<UVTransform>();
	uvTransform_->Initialize();

	// マテリアルの生成と初期化
	material_ = std::make_unique<Material>();
	material_->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void BaseMesh::Update()
{
	// マテリアルの更新処理
	material_->Update();

	// ワールドトランスフォームの更新
	worldTransform_->Update();

	// UVトランスフォームの更新
	uvTransform_->Update();
}