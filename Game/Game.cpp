#include "Game.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Game::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{

}