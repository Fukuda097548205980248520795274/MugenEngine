#include "ResourcesUVSphere.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void ResourcesUVSphere::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;


	/*---------------------------------------------
	    インデックスリソースの生成 と バッファの設定
	---------------------------------------------*/

	// リソース生成
	indexResource_ = CreateBufferResource(device_, sizeof(uint32_t) * (kMaxSegment * kMaxRing * 6));

	// バッファ設定
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * (kMaxSegment * kMaxRing * 6);
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	// データを割り当てる
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));


	/*-------------------------------------
	    頂点リソースの生成 と バッファの設定
	-------------------------------------*/

	// リソースの生成
	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataModel) * (kMaxSegment * kMaxRing * 4));

	// バッファ設定
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexDataModel) * (kMaxSegment * kMaxRing * 4);
	vertexBufferView_.StrideInBytes = sizeof(VertexDataModel);

	// データを割り当てる
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));


	/*---------------------------
	    マテリアルリソースの生成
	---------------------------*/

	// リソース生成
	materialResource_ = CreateBufferResource(device_, sizeof(MaterialDataModel));

	// データを割り当てる
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	materialData_->enableLighting_ = true;
	materialData_->enableHalfLambert_ = true;
	materialData_->uvTransform_ = MakeIdentityMatrix4x4();


	/*--------------------------
	    座標変換リソースの生成
	--------------------------*/

	// リソース生成
	transformationResource_ = CreateBufferResource(device_, sizeof(TransformationDataModel));

	// データを割り当てる
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	transformationData_->worldViewProjection = MakeIdentityMatrix4x4();
	transformationData_->world = MakeIdentityMatrix4x4();


	/*--------------------------
	    平行光源リソースの生成
	--------------------------*/

	// リソース生成
	directionalLightResource_ = CreateBufferResource(device_, sizeof(DirectionalLight));

	// データを割り当てる
	directionalLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData_));
	directionalLightData_->color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLightData_->direction = Vector3(0.0f, -1.0f, 0.0f);
	directionalLightData_->intensity = 1.0f;
}

/// <summary>
/// コマンドリストに設定を登録する
/// </summary>
void ResourcesUVSphere::SetCommandList()
{
	// インデックスリソースを設定
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点リソースを設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースを設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースを設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());

	// 平行光源リソースを設定
	commandList_->SetGraphicsRootConstantBufferView(3, directionalLightResource_->GetGPUVirtualAddress());
}