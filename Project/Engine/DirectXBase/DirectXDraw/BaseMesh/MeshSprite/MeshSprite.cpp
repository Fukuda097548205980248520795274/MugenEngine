#include "MeshSprite.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera2d"></param>
/// <param name="textureHandle"></param>
void MeshSprite::Initialize(const MugenEngine* engine, const Camera2D* camera2d, uint32_t textureHandle)
{
	// nullptrチェック
	assert(engine);
	assert(camera2d);

	// 引数を受け取る
	engine_ = engine;
	camera2d_ = camera2d;
	textureHandle_ = textureHandle;

	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform2D>();
	worldTransform_->Initialize();

	// UVトランスフォームの生成と初期化
	uvTransform_ = std::make_unique<UVTransform>();
	uvTransform_->Initialize();

	// テクスチャサイズを拡縮に反映する
	worldTransform_->scale_.x = engine_->GetTextureWidth(textureHandle_);
	worldTransform_->scale_.y = engine_->GetTextureHeight(textureHandle_);

	// 切り取りサイズを初期化する
	textureSize_.x = worldTransform_->scale_.x;
	textureSize_.y = worldTransform_->scale_.y;
}

/// <summary>
/// 更新処理
/// </summary>
void MeshSprite::Update()
{
#ifdef _DEBUG

	ImGui::Begin("Sprite");
	ImGui::DragFloat2("Scale", &worldTransform_->scale_.x, 1.0f);
	ImGui::DragFloat("rotation", &worldTransform_->rotation_, 0.01f);
	ImGui::DragFloat3("translation", &worldTransform_->translation_.x, 1.0f);
	ImGui::DragFloat2("Anchor", &anchor_.x, 0.1f);
	ImGui::DragFloat2("textureLeftTop", &textureLeftTop_.x, 1.0f);
	ImGui::DragFloat2("textureSize", &textureSize_.x, 1.0f);
	ImGui::End();

#endif

	// トランスフォームの更新
	worldTransform_->Update();
	uvTransform_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void MeshSprite::Draw()
{
	engine_->DrawSprite(worldTransform_.get(), anchor_, textureLeftTop_, textureSize_,
		uvTransform_.get(), camera2d_, textureHandle_, color_, isFlipX_, isFlipY_);
}