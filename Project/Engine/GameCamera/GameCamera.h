#pragma once
#include <memory>
#include "DirectXBase/DirectXDraw/Camera/Camera3D/Camera3D.h"

// 前方宣言
class MugenEngine;

class GameCamera
{
public:


	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// カメラのGetter
	/// </summary>
	/// <returns></returns>
	Camera3D GetCamera3D()const { return *camera3d_.get(); }


	// ピボットポイント
	Vector3 pivotPoint_ = Vector3(0.0f, 0.0f, 0.0f);

	// ピボットポイントとの距離
	float pointLength_ = 50.0f;


protected:

	// エンジン
	const MugenEngine* engine_ = nullptr;


	// 3Dカメラ
	std::unique_ptr<Camera3D> camera3d_ = nullptr;


};

