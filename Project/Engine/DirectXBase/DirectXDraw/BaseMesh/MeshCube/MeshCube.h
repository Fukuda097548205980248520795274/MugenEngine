#pragma once
#include "../BaseMesh.h"

class MeshCube : public BaseMesh
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera3d"></param>
	/// <param name="textureHandle"></param>
	void Initialize(const Camera3D* camera3d, TextureHandle textureHandle) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

