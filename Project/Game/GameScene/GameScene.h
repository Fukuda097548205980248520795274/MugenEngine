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


	// モデル
	std::unique_ptr<MeshModel> model0_ = nullptr;
	
};

