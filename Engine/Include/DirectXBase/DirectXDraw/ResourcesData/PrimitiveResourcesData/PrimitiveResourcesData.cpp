#include "PrimitiveResourcesData.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void PrimitiveResourcesData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;


	// マテリアル
	materialResource_ = CreateBufferResource(device_, sizeof(MaterialDataForGPU));
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	materialData_->uvTransform_ = MakeIdentityMatrix4x4();
	materialData_->enableLighting_ = true;
	materialData_->enableHalfLambert_ = false;
	materialData_->enableSpecular_ = false;
	materialData_->enableBlinnPhong_ = false;
	materialData_->shininess_ = 15.0f;

	// 座標変換
	transformationResource_ = CreateBufferResource(device_, sizeof(TransformationDataForGPU));
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	transformationData_->world = MakeIdentityMatrix4x4();
	transformationData_->worldInverseTranspose = MakeIdentityMatrix4x4();
	transformationData_->worldViewProjection = MakeIdentityMatrix4x4();
}

/// <summary>
/// インデックスリソースを生成する
/// </summary>
void PrimitiveResourcesData::CreateIndexResource(uint32_t numIndex)
{
	// リソース生成
	indexResource_ = CreateBufferResource(device_, sizeof(uint32_t) * numIndex);

	// バッファの設定
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * numIndex;
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	// データを割り当てる
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));
}

/// <summary>
/// 頂点リソースを生成する
/// </summary>
/// <param name="numVertex"></param>
void PrimitiveResourcesData::CreateVertexResource(uint32_t numVertex)
{
	// リソース生成
	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataForGPU) * numVertex);

	// バッファの設定
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexDataForGPU) * numVertex;
	vertexBufferView_.StrideInBytes = sizeof(VertexDataForGPU);

	// データを割り当てる
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
}