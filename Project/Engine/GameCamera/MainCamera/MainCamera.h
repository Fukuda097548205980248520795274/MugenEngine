#pragma once
#include "GameCamera/GameCamera.h"
#include "DirectXBase/DirectXDraw/BaseMesh/MeshOptions/WorldTransform3D/WorldTransform3D.h"

class MainCamera : public GameCamera
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const MugenEngine* engine) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// ピボットポイント位置のSetter
	/// </summary>
	/// <param name="pivotPoint"></param>
	void SetPivotPoint(const Vector3 pivotPoint) { pivotPoint_ = pivotPoint; }

	// 回転
	Vector3 pointRotation_ = Vector3(0.0f, 0.0f, 0.0f);
};

