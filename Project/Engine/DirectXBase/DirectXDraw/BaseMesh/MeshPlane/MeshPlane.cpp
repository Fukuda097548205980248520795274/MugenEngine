#include "MeshPlane.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="textureHandle"></param>
void MeshPlane::Initialize(const MugenEngine* engine, const Camera3D* camera3d, TextureHandle textureHandle)
{
	// 基底クラスの初期化
	BaseMesh::Initialize(engine, camera3d, textureHandle);
}

/// <summary>
/// 描画処理
/// </summary>
void MeshPlane::Draw()
{
	// 立方体を描画する
	engine_->DrawPlane(worldTransform_.get(), uvTransform_.get(), camera3d_, textureHandle_, material_.get());
}