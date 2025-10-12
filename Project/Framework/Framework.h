#pragma once
#include "MugenEngine.h"

class Framework
{
public:

	/// <summary>
	/// 実行
	/// </summary>
	void Run(int32_t clientWidth, int32_t clientHeight, const std::string& title);


protected:

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;


	// エンジン
	MugenEngine* engine_ = nullptr;
};

