#include "Engine/Include/MugenEngine.h"
#include "Game/Game.h"

// Windowsアプリでの main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 無限エンジンの生成と初期化
	MugenEngine* mugenEngine = new MugenEngine();
	mugenEngine->Initialize(1280, 720, "LE2A_11_フクダ_ソウワ");

	// ゲームの生成と初期化
	Game* game = new Game();
	game->Initialize(mugenEngine);

	// ゲームループ
	while (mugenEngine->ProcessMessage())
	{
		// 全ての入力情報を取得する
		mugenEngine->CheckInputInfo();

		// オーディオストアの更新処理
		mugenEngine->UpdateAudioStore();

		// 描画前処理
		mugenEngine->PreDraw();

		// ゲームの更新処理
		game->Update();

		// ゲームの描画処理
		game->Draw();

		// 描画後処理
		mugenEngine->PostDraw();

		// 全ての入力情報をコピーする
		mugenEngine->CopyInputInfo();
	}

	// ゲームの削除
	delete game;
	game = nullptr;

	// 無限エンジンの削除
	delete mugenEngine;
	mugenEngine = nullptr;

	return 0;
}