#include "ResourcesParticleCube.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void ResourcesParticleCube::Initialize(DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t numParticle)
{
	// nullptrチェック
	assert(directXHeap);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	directXHeap_ = directXHeap;
	device_ = device;
	commandList_ = commandList;
	numParticles_ = numParticle;


	/*------------------------------
		インデックスリソースの生成
	------------------------------*/

	// リソース生成
	indexResource_ = CreateBufferResource(device_, sizeof(uint32_t) * (kNumMesh * 6));

	// バッファ設定
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * (kNumMesh * 6);
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	// データを割り当てる
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));

	// 番号を与える
	for (int32_t i = 0; i < kNumMesh; ++i)
	{
		int32_t startIndex = i * 6;
		int32_t index = i * 4;

		indexData_[startIndex] = index;
		indexData_[startIndex + 1] = index + 1;
		indexData_[startIndex + 2] = index + 2;
		indexData_[startIndex + 3] = index + 1;
		indexData_[startIndex + 4] = index + 3;
		indexData_[startIndex + 5] = index + 2;
	}


	/*----------------------
		頂点リソースの生成
	----------------------*/

	// リソースの生成
	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataModelForGPU) * ((kNumMesh) * 4));

	// バッファ設定
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexDataModelForGPU) * ((kNumMesh) * 4);
	vertexBufferView_.StrideInBytes = sizeof(VertexDataModelForGPU);

	// データを割り当てる
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	// ローカル座標を与える
	vertexData_[0].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[0].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[1].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[1].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[2].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[2].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[3].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[3].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[3].normal = Vector3(0.0f, 0.0f, -1.0f);

	vertexData_[4].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[4].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[4].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[5].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[5].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[5].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[6].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[6].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[6].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[7].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[7].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[7].normal = Vector3(1.0f, 0.0f, 0.0f);

	vertexData_[8].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[8].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[8].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[9].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[9].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[9].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[10].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[10].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[10].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[11].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[11].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[11].normal = Vector3(0.0f, 0.0f, 1.0f);

	vertexData_[12].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[12].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[12].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[13].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[13].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[13].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[14].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[14].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[14].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[15].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[15].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[15].normal = Vector3(-1.0f, 0.0f, 0.0f);

	vertexData_[16].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[16].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[16].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[17].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[17].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[17].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[18].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[18].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[18].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[19].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[19].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[19].normal = Vector3(0.0f, 1.0f, 0.0f);

	vertexData_[20].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[20].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[20].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[21].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[21].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[21].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[22].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[22].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[22].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[23].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[23].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[23].normal = Vector3(0.0f, -1.0f, 0.0f);


	/*---------------------------
		マテリアルリソースの生成
	---------------------------*/

	// リソース生成
	materialResource_ = CreateBufferResource(device_, sizeof(MaterialDataModelForGPU));

	// データを割り当てる
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	materialData_->enableLighting_ = true;
	materialData_->enableHalfLambert_ = true;
	materialData_->uvTransform_ = MakeIdentityMatrix4x4();


	/*-------------------------
		座標変換リソースの生成
	-------------------------*/

	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvTransformationDesc{};
	srvTransformationDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvTransformationDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvTransformationDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvTransformationDesc.Buffer.FirstElement = 0;
	srvTransformationDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvTransformationDesc.Buffer.NumElements = numParticles_;
	srvTransformationDesc.Buffer.StructureByteStride = sizeof(TransformationDataModelForGPU);

	// ディスクリプタハンドルを取得する
	cpuTransformationHandle_ = directXHeap_->GetSrvCPUDescriptorHandle();
	gpuTransformationHandle_ = directXHeap_->GetSrvGPUDescriptorHandle();

	// ビューを生成する
	device_->CreateShaderResourceView(instancingTransformationResource_.Get(), &srvTransformationDesc, cpuTransformationHandle_);


	// リソース生成
	instancingTransformationResource_ = CreateBufferResource(device_, sizeof(TransformationDataModelForGPU) * numParticles_);

	// データを割り当てる
	instancingTransformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	for (uint32_t i = 0; i < numParticles_; ++i)
	{
		transformationData_[i].worldViewProjection = MakeIdentityMatrix4x4();
		transformationData_[i].world = MakeIdentityMatrix4x4();
	}


	/*-------------------------
		平行光源リソースの生成
	-------------------------*/

	// リソース生成
	directionalLightResource_ = CreateBufferResource(device_, sizeof(DirectionalLightForGPU));

	// データを割り当てる
	directionalLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData_));
	directionalLightData_->color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLightData_->direction = Vector3(0.0f, -1.0f, 0.0f);
	directionalLightData_->intensity = 1.0f;
}


/// <summary>
/// コマンドリストに設定を登録する
/// </summary>
void ResourcesParticleCube::SetCommandList() const
{
	// インデックスリソースの設定
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点リソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースの設定
	commandList_->SetGraphicsRootDescriptorTable(1, gpuTransformationHandle_);

	// 平行光源リソースを設定
	commandList_->SetGraphicsRootConstantBufferView(3, directionalLightResource_->GetGPUVirtualAddress());
}