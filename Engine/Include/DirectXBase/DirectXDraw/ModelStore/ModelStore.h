#pragma once
#include "../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../../Func/LoadModel/LoadModel.h"
#include "../TextureStore/TextureStore.h"
#include "../DataForGPU/MaterialData/MaterialData.h"
#include "../DataForGPU/TransformationData/TransformationData.h"
#include "../ResourcesData/IndexVertexData/IndexVertexData.h"

// 格納されたモデルデータ
class ModelInfoDatum
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device_"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device_, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	void Register(UINT materialRootParameterIndex , UINT transformationRootParameterIndex);

	// モデルデータ
	std::vector<ModelData> modelData_{};

	// モデルハンドル
	uint32_t modelHandle_;

	// ファイルパス
	std::string filePath_;

	// テクスチャハンドル
	std::vector<uint32_t> textureHandle_;

	// インデックスと頂点のデータ
	std::vector<std::unique_ptr<IndexVertexData>> indexVertexResource_{};

	// マテリアルデータ
	MaterialDataForGPU* materialData_ = nullptr;

	// 座標変換データ
	TransformationDataForGPU* transformationData_ = nullptr;


private:

	// デバイス
	ID3D12Device* device_;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_;


	// マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;

	// 座標変換リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource_ = nullptr;
};


class ModelStore
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textureStore"></param>
	void Initialize(TextureStore* textureStore, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// モデルを読み込む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	uint32_t LoadModel(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// モデルの情報のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	ModelInfoDatum* GetModelInfo(uint32_t modelHandle)const { return modelInfoData_[modelHandle].get(); }


private:

	// テクスチャストア
	TextureStore* textureStore_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// 格納されたモデルデータ
	std::vector<std::unique_ptr<ModelInfoDatum>> modelInfoData_;
};

