#include "ResourcesTriangle.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void ResourcesTriangle::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;



	/*----------------------
		頂点リソースの作成
	----------------------*/

	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataModel) * 6);


	/*-------------------------------
		頂点リソースのビューを設定する
	-------------------------------*/

	// リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();

	vertexBufferView_.SizeInBytes = sizeof(VertexDataModel) * 6;
	vertexBufferView_.StrideInBytes = sizeof(VertexDataModel);


	/*----------------------------------
		頂点データをリソースに割り当てる
	----------------------------------*/

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	// 左下
	vertexData_[0].position = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
	vertexData_[0].texcoord = Vector2(0.0f, 1.0f);

	// 上
	vertexData_[1].position = Vector4(0.0f, 0.5f, 0.0f, 1.0f);
	vertexData_[1].texcoord = Vector2(0.5f, 0.0f);

	// 右下
	vertexData_[2].position = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
	vertexData_[2].texcoord = Vector2(1.0f, 1.0f);

	// 左下2
	vertexData_[3].position = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
	vertexData_[3].texcoord = Vector2(0.0f, 1.0f);

	// 上2
	vertexData_[4].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[4].texcoord = Vector2(0.5f, 0.0f);

	// 右下2
	vertexData_[5].position = Vector4(0.5f, -0.5f, -0.5f, 1.0f);
	vertexData_[5].texcoord = Vector2(1.0f, 1.0f);



	/*--------------------------------------
		マテリアルリソースの作成とデータの設定
	--------------------------------------*/

	materialResource_ = CreateBufferResource(device_, sizeof(Vector4));

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	*materialData_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);


	/*-------------------------------------
	    座標変換リソースの作成とデータの設定
	-------------------------------------*/

	transformationResource_ = CreateBufferResource(device_, sizeof(Matrix4x4));

	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	*transformationData_ = MakeIdentityMatrix();
}


/// <summary>
/// コマンドリストに設定を登録する
/// </summary>
void ResourcesTriangle::SetCommandList()
{
	// 頂点バッファリソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースの設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
}