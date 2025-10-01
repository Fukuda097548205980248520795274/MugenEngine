#pragma once
#include "MugenEngine.h"

#include "GameScene/GameScene.h"

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


	// ゲームシーン
	std::unique_ptr<Scene> scene_ = nullptr;
};

