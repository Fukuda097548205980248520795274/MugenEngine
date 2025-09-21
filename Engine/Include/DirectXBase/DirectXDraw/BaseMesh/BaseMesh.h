#pragma once
#include <memory>
#include "WorldTransform3D/WorldTransform3D.h"
#include "UVTransform/UVTransform.h"
#include "../Camera/Camera3D/Camera3D.h"

// 前方宣言
class MugenEngine;

class BaseMesh
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera3d"></param>
	/// <param name="textureHandle"></param>
	virtual void Initialize(const MugenEngine* engine, const Camera3D* camera3d, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform3D> worldTransform_ = nullptr;

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 色
	Vector4 color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	// ライティング有効化
	bool enableLighting_ = true;

	// ハーフランバート有効化
	bool enableHalfLambert_ = false;


protected:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera3D* camera3d_ = nullptr;
};

