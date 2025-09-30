#pragma once
#include "MugenEngine.h"

class Game
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	std::unique_ptr<Camera3D> camera3d_ = nullptr;

	// 2Dカメラ
	std::unique_ptr<Camera2D> camera2d_ = nullptr;

	
	// モデル
	std::unique_ptr<MeshModel> model_ = nullptr;

	// モデルハンドル
	uint32_t modelHandle_ = 0;


	// UV球
	std::unique_ptr<MeshUVSphere> uvSphere_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;


	// サウンドハンドル
	uint32_t soundHandle_ = 0;

	// プレイハンドル
	uint32_t playHandle_ = 0;
};

