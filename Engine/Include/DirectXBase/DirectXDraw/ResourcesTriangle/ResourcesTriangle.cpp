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

	// ヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;

	// 頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeof(Vector4) * 3;

	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;

	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点リソースを作る
	HRESULT hr = device_->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource_));
	assert(SUCCEEDED(hr));


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
}


/// <summary>
/// コマンドリストに設定を登録する
/// </summary>
void ResourcesTriangle::SetCommandList()
{
	// 頂点バッファリソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);
}