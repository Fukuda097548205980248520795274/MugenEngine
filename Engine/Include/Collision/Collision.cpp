#include "Collision.h"
#include "../MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Collision::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
}