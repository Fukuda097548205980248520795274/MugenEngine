#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../MeshOptions/WorldTransform3D/WorldTransform3D.h"
#include "../MeshOptions/UVTransform/UVTransform.h"
#include "../MeshOptions/Material/Material.h"
#include "../../Camera/Camera3D/Camera3D.h"
#include "Handle/Handle.h"

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
	void Initialize(const Camera3D* camera3d, ModelHandle modelHandle);

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
	void SetModelHandle(ModelHandle modelHandle) { modelHandle_ = modelHandle; }

	/// <summary>
	/// アニメーション速度のSetter
	/// </summary>
	/// <param name="animationSpeed"></param>
	void SetAnimationSpeed(float animationSpeed) { animationSpeed_ = animationSpeed; }

	/// <summary>
	/// メッシュ名を指定してマテリアルを取得する
	/// </summary>
	/// <param name="meshName"></param>
	/// <returns></returns>
	Material* GetMateril(const std::string& meshName);

	/// <summary>
	/// メッシュ名を指定してUVトランスフォームを取得する
	/// </summary>
	/// <param name="meshName"></param>
	/// <returns></returns>
	UVTransform* GetUVTransform(const std::string& meshName);


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform3D> worldTransform_ = nullptr;


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera3D* camera3d_ = nullptr;

	// モデルハンドル
	ModelHandle modelHandle_{};

	// メッシュ数
	uint32_t numMesh_ = 0;


	// UVトランスフォーム
	std::vector<std::unique_ptr<UVTransform>> uvTransform_;

	// マテリアル
	std::vector<std::unique_ptr<Material>> material_;

	// UVトランスフォーム
	std::vector<UVTransform*> uvTransformP_;

	// マテリアル
	std::vector<Material*> materialP_;



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

