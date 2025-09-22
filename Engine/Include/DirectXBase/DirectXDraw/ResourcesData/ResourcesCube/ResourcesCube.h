#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"

#include "../../DataForGPU/VertexData/VertexData.h"
#include "../../DataForGPU/MaterialData/MaterialData.h"
#include "../../DataForGPU/TransformationData/TransformationData.h"
#include "../../DataForGPU/LightData/LightData.h"

class ResourcesCube
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// コマンドリストに設定を登録する
	/// </summary>
	void SetCommandList();


	// インデックスデータ
	uint32_t* indexData_ = nullptr;

	// 頂点データ
	VertexDataModelForGPU* vertexData_ = nullptr;

	// マテリアルデータ
	MaterialDataModelForGPU* materialData_ = nullptr;

	// 座標変換データ
	TransformationDataModelForGPU* transformationData_ = nullptr;

	// 平行光源データ
	DirectionalLightForGPU* directionalLightData_ = nullptr;



private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// 面の数
	const int32_t kNumMesh = 6;


	// インデックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;

	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};


	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};


	// マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;


	// 座標変換リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource_ = nullptr;


	// 平行光源リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_ = nullptr;
};

