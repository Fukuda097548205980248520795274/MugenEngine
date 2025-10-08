#pragma once
#include <memory>
#include "MeshOptions/WorldTransform3D/WorldTransform3D.h"
#include "MeshOptions/UVTransform/UVTransform.h"
#include "MeshOptions/Material/Material.h"
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

	/// <summary>
	/// 親ワールドトランスフォームのSetter
	/// </summary>
	/// <param name="worldTransform"></param>
	void SetParent(const WorldTransform3D* worldTransform) { worldTransform_->SetParent(worldTransform); }


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform3D> worldTransform_ = nullptr;

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// マテリアル
	std::unique_ptr<Material> material_ = nullptr;


protected:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera3D* camera3d_ = nullptr;
};

