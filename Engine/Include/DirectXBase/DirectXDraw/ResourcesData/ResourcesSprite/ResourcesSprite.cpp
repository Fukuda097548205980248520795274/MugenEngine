#include "ResourcesSprite.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void ResourcesSprite::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;


	/*------------------------------
		インデックスリソースの生成
	------------------------------*/

	// リソース生成
	indexResource_ = CreateBufferResource(device_, sizeof(uint32_t) * 6);

	// バッファ設定
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * 6;
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	// データを割り当てる
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));

	// 番号を割り当てる
	indexData_[0] = 0;
	indexData_[1] = 1;
	indexData_[2] = 2;
	indexData_[3] = 1;
	indexData_[4] = 3;
	indexData_[5] = 2;


	/*----------------------
	    頂点リソースの生成
	----------------------*/

	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataModelForGPU) * 4);

	// リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexDataModelForGPU) * 4;
	vertexBufferView_.StrideInBytes = sizeof(VertexDataModelForGPU);

	// 頂点データをリソースに割り当てる
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	// 左下
	vertexData_[0].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[0].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[0].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 左上
	vertexData_[1].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[1].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[1].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 右下
	vertexData_[2].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[2].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[2].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 右上
	vertexData_[3].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[3].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[3].normal = Vector3(0.0f, 0.0f, -1.0f);


	/*--------------------------------------
		マテリアルリソースの作成とデータの設定
	--------------------------------------*/

	materialResource_ = CreateBufferResource(device_, sizeof(MaterialDataModelForGPU));
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));

	materialData_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	materialData_->uvTransform_ = MakeIdentityMatrix4x4();

	// ライティングは行わない
	materialData_->enableLighting_ = false;
	materialData_->enableHalfLambert_ = false;


	/*-------------------------------------
		座標変換リソースの作成とデータの設定
	-------------------------------------*/

	transformationResource_ = CreateBufferResource(device_, sizeof(TransformationDataModelForGPU));
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));

	transformationData_->worldViewProjection = MakeIdentityMatrix4x4();
	transformationData_->world = MakeIdentityMatrix4x4();
}

/// <summary>
/// コマンドリストに設定を登録する
/// </summary>
void ResourcesSprite::SetCommandList()
{
	// インデックスバッファリソースの設定
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点バッファリソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースの設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
}