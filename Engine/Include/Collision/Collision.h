#pragma once
#include <cassert>

// 前方宣言
class MugenEngine;

class Collision
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine);


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;
};

