#include "Game.h"

// Windowsアプリでの main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ゲームの実行
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->Run(1280, 720, "LE2A_12_フクダ_ソウワ");

	return 0;
}