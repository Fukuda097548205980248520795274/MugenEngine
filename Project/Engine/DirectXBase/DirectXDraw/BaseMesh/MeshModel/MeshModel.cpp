#include "MeshModel.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="camera3d"></param>
/// <param name="modelHandle"></param>
void MeshModel::Initialize(const MugenEngine* engine, const Camera3D* camera3d, ModelHandle modelHandle)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	modelHandle_ = modelHandle;

	// メッシュ数を取得する
	numMesh_ = engine_->GetNumMesh(modelHandle);

	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform3D>();
	worldTransform_->Initialize();

	for (uint32_t i = 0; i < numMesh_; ++i)
	{
		// UVトランスフォームの生成と初期化
		std::unique_ptr<UVTransform> uvTransform = std::make_unique<UVTransform>();
		uvTransform->Initialize();

		// マテリアルの生成と初期化
		std::unique_ptr<Material> material = std::make_unique<Material>();
		material->Initialize();

		// リストに登録する
		uvTransformP_.push_back(uvTransform.get());
		materialP_.push_back(material.get());
		uvTransform_.push_back(std::move(uvTransform));
		material_.push_back(std::move(material));
	}

	// アニメーションが有効かどうか
	isAnimation_ = engine_->IsAnimation(modelHandle_);

	// アニメーション時間を取得する
	if (isAnimation_)
		duration_ = engine_->GetAnimationDuration(modelHandle_);
}

/// <summary>
/// 更新処理
/// </summary>
void MeshModel::Update()
{
	// アニメーションの更新処理
	if (isAnimation_)
		UpdateAnimation();

	// マテリアルの更新処理
	for (std::unique_ptr<Material>& material : material_)
	{
		material->Update();
	}

	// ワールドトランスフォームの更新
	worldTransform_->Update();

	// UVトランスフォームの更新
	for (std::unique_ptr<UVTransform>& uvTransform : uvTransform_)
	{
		uvTransform->Update();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void MeshModel::Draw()
{
	// マテリアルの更新処理
	for (std::unique_ptr<Material>& material : material_)
	{
		
	}

	// UVトランスフォームの更新
	for (std::unique_ptr<UVTransform>& uvTransform : uvTransform_)
	{
		
	}

	// モデルを描画する
	engine_->DrawModel(worldTransform_.get(), uvTransformP_, camera3d_, modelHandle_, materialP_, animationTimer_);
}

/// <summary>
/// アニメーションの更新処理
/// </summary>
void MeshModel::UpdateAnimation()
{
	// アニメーションタイマーを進める
	animationTimer_ += engine_->GetDeltaTime() * animationSpeed_;

	// 時間を越えらた周回する
	animationTimer_ = std::fmod(animationTimer_, duration_);
}