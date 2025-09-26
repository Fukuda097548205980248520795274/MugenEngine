#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/VertexData/VertexData.h"

class IndexVertexData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="indexNum"></param>
	/// <param name="vertexNum"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t indexNum, uint32_t vertexNum);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	void Register();

	/// <summary>
	/// インデックス数のGetter
	/// </summary>
	/// <returns></returns>
	UINT GetIndexNum()const { return UINT(indexNum_); }

	// インデックスデータ
	uint32_t* indexData_ = nullptr;

	// 頂点データ
	VertexDataForGPU* vertexData_ = nullptr;


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// インデックス数
	uint32_t indexNum_ = 0;

	// 頂点数
	uint32_t vertexNum_ = 0;


	// インデックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;

	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};


	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
};

