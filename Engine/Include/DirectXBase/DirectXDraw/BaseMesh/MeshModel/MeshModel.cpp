#include "MeshModel.h"
#include "../../../../MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="camera3d"></param>
/// <param name="modelHandle"></param>
void MeshModel::Initialize(const MugenEngine* engine, const Camera3D* camera3d, uint32_t modelHandle)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	modelHandle_ = modelHandle;

	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform3D>();
	worldTransform_->Initialize();

	// UVトランスフォームの生成と初期化
	uvTransform_ = std::make_unique<UVTransform>();
	uvTransform_->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void MeshModel::Update()
{
	// ワールドトランスフォームの更新
	worldTransform_->Update();

	// UVトランスフォームの更新
	uvTransform_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void MeshModel::Draw()
{
	// モデルを描画する
	engine_->DrawModel(worldTransform_.get(), uvTransform_.get(), camera3d_, modelHandle_, color_, enableLighting_, enableHalfLambert_);
}