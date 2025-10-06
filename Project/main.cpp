#include "MugenEngine.h"
#include "Game.h"

// Windowsアプリでの main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 無限エンジンの生成と初期化
	MugenEngine* mugenEngine = new MugenEngine();
	mugenEngine->Initialize(1280, 720, "LE2A_12_フクダ_ソウワ");

	// ゲームの生成と初期化
	Game* game = new Game();
	game->Initialize(mugenEngine);

	// ゲームループ
	while (mugenEngine->ProcessMessage())
	{
		// フレーム開始処理
		mugenEngine->FrameStart();


		///
		/// ↓ 更新処理ここから
		/// 

		// ゲームの更新処理
		game->Update();

		///
		/// ↑ 更新処理ここまで
		/// 

		

		///
		/// ↓ 描画処理ここから
		/// 

		// ゲームの描画処理
		game->Draw();

		///
		/// ↑ 描画処理ここまで
		/// 


		// フレーム終了処理
		mugenEngine->FrameEnd();
	}

	// ゲームの削除
	delete game;
	game = nullptr;

	// 無限エンジンの削除
	delete mugenEngine;
	mugenEngine = nullptr;

	return 0;
}