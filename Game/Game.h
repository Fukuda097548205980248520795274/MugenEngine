#pragma once
#include "../Engine/Include/MugenEngine.h"

class Game
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	std::unique_ptr<Camera3D> camera3d_ = nullptr;

	
	// 立方体
	std::unique_ptr<MeshCube> cube_ = nullptr;


	// サウンドハンドル
	uint32_t soundHandle_ = 0;

	// プレイハンドル
	uint32_t playHandle_ = 0;
};

