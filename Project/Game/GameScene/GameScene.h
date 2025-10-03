#pragma once
#include "MugenEngine.h"

class GameScene : public Scene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


public:



	// モデル2
	std::unique_ptr<MeshModel> model2_ = nullptr;

	// モデルハンドル2
	uint32_t modelHandle2_ = 0;


	// モデル1
	std::unique_ptr<MeshModel> model1_ = nullptr;

	// モデルハンドル1
	uint32_t modelHandle1_ = 0;


	// タイマー
	float timer_ = 0.0f;
};

