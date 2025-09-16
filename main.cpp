#include "Engine/Include/MugenEngine.h"

// Windowsアプリでの main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 無限エンジンの生成と初期化
	MugenEngine* mugenEngine = new MugenEngine();
	mugenEngine->Initialize(1280, 720, "LE2A_11_フクダ_ソウワ");


	// uvChecker
	uint32_t ghUvChecker = mugenEngine->LoadTexture("./Resources/Textures/uvChecker.png");


	// ゲームループ
	while (mugenEngine->ProcessMessage())
	{
		// 描画前処理
		mugenEngine->PreDraw();


		// 三角形を描画する
		mugenEngine->DrawTriangle(ghUvChecker);


		// 描画後処理
		mugenEngine->PostDraw();
	}

	// 無限エンジンの削除
	delete mugenEngine;
	mugenEngine = nullptr;

	return 0;
}