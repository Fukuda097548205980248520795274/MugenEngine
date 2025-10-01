#pragma once
#include "GameCamera/MainCamera/MainCamera.h"
#include "GameCamera/DebugCamera/DebugCamera.h"

class Scene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	virtual void Initialize(const MugenEngine* engine);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();


protected:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// 3Dカメラ
	std::unique_ptr<Camera3D> camera3d_ = nullptr;


private:


	// メインカメラ
	std::unique_ptr<MainCamera> mainCamera_ = nullptr;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;


	// デバッグモード有効化
	bool enableDebug_ = false;
};

