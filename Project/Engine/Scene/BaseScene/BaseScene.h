#pragma once
#include "DirectXBase/DirectXDraw/Camera/Camera2D/Camera2D.h"
#include "GameCamera/MainCamera/MainCamera.h"
#include "GameCamera/DebugCamera/DebugCamera.h"

// 前方宣言
class SceneManager;

class BaseScene
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

	// 2Dカメラ
	std::unique_ptr<Camera2D> camera2d_ = nullptr;

	// メインカメラ
	std::unique_ptr<MainCamera> mainCamera_ = nullptr;

	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;


private:

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;


	// デバッグモード有効化
	bool enableDebug_ = false;
};

