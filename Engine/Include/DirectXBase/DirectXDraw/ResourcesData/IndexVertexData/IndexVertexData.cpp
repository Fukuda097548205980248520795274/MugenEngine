#include "IndexVertexData.h"


/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <param name="indexNum"></param>
/// <param name="vertexNum"></param>
void IndexVertexData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t indexNum, uint32_t vertexNum)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	indexNum_ = indexNum;
	vertexNum_ = vertexNum;


	/*-----------------------------
	    インデックスリソースの準備
	-----------------------------*/

	// リソース生成
	indexResource_ = CreateBufferResource(device_, sizeof(uint32_t) * indexNum_);

	// ビューの設定
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * indexNum_;
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	// データを割り当てる
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));


	/*----------------------
	    頂点リソースの準備
	----------------------*/

	// リソース生成
	vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataForGPU) * vertexNum_);

	// ビューの設定
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	vertexBufferView_.SizeInBytes = sizeof(VertexDataForGPU) * vertexNum_;
	vertexBufferView_.StrideInBytes = sizeof(VertexDataForGPU);

	// データを割り当てる
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
void IndexVertexData::Register()
{
	// インデックス
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);
}