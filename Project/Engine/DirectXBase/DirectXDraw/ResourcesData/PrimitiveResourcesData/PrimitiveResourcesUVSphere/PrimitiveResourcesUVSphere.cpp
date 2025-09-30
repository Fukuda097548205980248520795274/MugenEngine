#include "PrimitiveResourcesUVSphere.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void PrimitiveResourcesUVSphere::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// 基底クラスの初期化
	PrimitiveResourcesData::Initialize(device, commandList);

	// インデックスリソースを生成する
	CreateIndexResource(kMaxSegment * kMaxRing * 6);

	// 頂点リソースを生成する
	CreateVertexResource(kMaxSegment * kMaxRing * 4);
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
void PrimitiveResourcesUVSphere::Register()
{
	// インデックスリソースの設定
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点リソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースの設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
}