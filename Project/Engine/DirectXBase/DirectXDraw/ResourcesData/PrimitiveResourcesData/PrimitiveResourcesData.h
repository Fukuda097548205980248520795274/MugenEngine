#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"

#include "../../DataForGPU/VertexData/VertexData.h"
#include "../../DataForGPU/MaterialData/MaterialData.h"
#include "../../DataForGPU/TransformationData/TransformationData.h"

class PrimitiveResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	virtual void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 登録する
	/// </summary>
	virtual void Register() = 0;

	/// <summary>
	/// インデックスリソースを生成する
	/// </summary>
	void CreateIndexResource(uint32_t numIndex);

	/// <summary>
	/// 頂点リソースを生成する
	/// </summary>
	/// <param name="numVertex"></param>
	void CreateVertexResource(uint32_t numVertex);




	// インデックスデータ
	uint32_t* indexData_ = nullptr;

	// 頂点データ
	VertexDataForGPU* vertexData_ = nullptr;


protected:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// インデックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;

	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};


	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
};

