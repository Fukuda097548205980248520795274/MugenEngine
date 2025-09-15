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

	vertexResource_ = CreateBufferResource(device_, sizeof(Vector4) * 3);


	/*-------------------------------
		頂点リソースのビューを設定する
	-------------------------------*/

	// リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();

	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;
	vertexBufferView_.StrideInBytes = sizeof(Vector4);


	/*----------------------------------
		頂点データをリソースに割り当てる
	----------------------------------*/

	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	// 左下
	vertexData_[0] = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);

	// 上
	vertexData_[1] = Vector4(0.0f, 0.5f, 0.0f, 1.0f);

	// 右下
	vertexData_[2] = Vector4(0.5f, -0.5f, 0.0f, 1.0f);



	/*--------------------------------------
		マテリアルリソースの作成とデータの設定
	--------------------------------------*/

	materialResource_ = CreateBufferResource(device_, sizeof(Vector4));

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	*materialData_ = Vector4(1.0f, 0.0f, 0.0f, 1.0f);


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