#pragma once
#include <memory>
#include "../MeshOptions/WorldTransform3D/WorldTransform3D.h"
#include "../MeshOptions/UVTransform/UVTransform.h"
#include "../MeshOptions/Material/Material.h"
#include "../../Camera/Camera3D/Camera3D.h"

// 前方宣言
class MugenEngine;

class MeshModel
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera3d"></param>
	/// <param name="modelHandle"></param>
	void Initialize(const MugenEngine* engine, const Camera3D* camera3d, uint32_t modelHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 親ワールドトランスフォームのSetter
	/// </summary>
	/// <param name="worldTransform"></param>
	void SetParent(const WorldTransform3D* worldTransform) { worldTransform_->SetParent(worldTransform); }

	/// <summary>
	/// モデルハンドルのSetter
	/// </summary>
	/// <param name="modelHandle"></param>
	void SetModelHandle(uint32_t modelHandle) { modelHandle_ = modelHandle; }

	/// <summary>
	/// アニメーション速度のSetter
	/// </summary>
	/// <param name="animationSpeed"></param>
	void SetAnimationSpeed(float animationSpeed) { animationSpeed_ = animationSpeed; }


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform3D> worldTransform_ = nullptr;

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = nullptr;

	// マテリアル
	std::unique_ptr<Material> material_ = nullptr;


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera3D* camera3d_ = nullptr;

	// モデルハンドル
	uint32_t modelHandle_ = 0;



	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	void UpdateAnimation();

	// アニメーション有効化
	bool isAnimation_ = false;

	// アニメーションタイマー
	float animationTimer_ = 0.0f;

	// アニメーション速度
	float animationSpeed_ = 1.0f;

	// アニメーション時間
	float duration_ = 0.0f;
};

