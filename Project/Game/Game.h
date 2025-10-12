#pragma once
#include "Framework/Framework.h"
#include "GameScene/GameScene.h"

class Game : public Framework
{
protected:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;


private:

	// ゲームシーン
	std::unique_ptr<Scene> scene_ = nullptr;
};

