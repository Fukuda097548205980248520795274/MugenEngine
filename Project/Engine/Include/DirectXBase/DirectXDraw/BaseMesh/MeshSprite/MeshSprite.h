#pragma once
#include <memory>
#include "../MeshOptions/WorldTransform2D/WorldTransform2D.h"
#include "../MeshOptions/UVTransform/UVTransform.h"
#include "../../Camera/Camera2D/Camera2D.h"

// 前方宣言
class MugenEngine;

class MeshSprite
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera2d"></param>
	/// <param name="textureHandle"></param>
	void Initialize(const MugenEngine* engine, const Camera2D* camera2d, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform2D> worldTransform_ = nullptr;

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// アンカーポイント
	Vector2 anchor_ = Vector2(0.0f, 0.0f);

	// 色
	Vector4 color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera2D* camera2d_ = nullptr;
};

