#include "MeshCube.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="textureHandle"></param>
void MeshCube::Initialize(const Camera3D* camera3d, TextureHandle textureHandle)
{
	// 基底クラスの初期化
	BaseMesh::Initialize(camera3d, textureHandle);
}

/// <summary>
/// 描画処理
/// </summary>
void MeshCube::Draw()
{
	// 立方体を描画する
	engine_->DrawCube(worldTransform_.get(), uvTransform_.get(), camera3d_, textureHandle_, material_.get());
}