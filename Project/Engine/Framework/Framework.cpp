#include "Framework.h"

/// <summary>
/// 実行
/// </summary>
void Framework::Run(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// エンジンのインスタンスの取得と初期化
	engine_ = MugenEngine::GetInstance();
	engine_->Initialize(clientWidth, clientHeight, title);

	// 初期化
	Initialize();

	// ゲームループ
	while (engine_->ProcessMessage())
	{
		// フレーム開始
		engine_->FrameStart();

		// 更新処理
		Update();

		// 描画処理
		Draw();

		// フレーム終了
		engine_->FrameEnd();
	}

	// エンジンの終了処理
	engine_->Finalize();

	// 解放漏れチェック
	LeakChecker();
}