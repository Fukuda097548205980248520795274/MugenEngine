#include "TitleScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void TitleScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	BaseScene::Initialize(engine);

	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(engine_, camera3d_.get(), Vector3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
	// 基底クラスの更新処理
	BaseScene::Update();

	// プレイヤーの更新処理
	player_->Update();



#ifdef _DEVELOPMENT
	if (ImGui::Button("GameScene"))
	{
		sceneManager_->SceneTransition("GAME");
	}
#endif
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	// プレイヤーの描画処理
	player_->Draw();

	// 基底クラスの描画処理
	BaseScene::Draw();
}