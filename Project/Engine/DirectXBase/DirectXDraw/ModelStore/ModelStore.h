#pragma once
#include "../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../../Func/LoadModel/LoadModel.h"
#include "Animation/Animation.h"
#include "Skeleton/Skeleton.h"
#include "../TextureStore/TextureStore.h"
#include "../DataForGPU/MaterialData/MaterialData.h"
#include "../DataForGPU/TransformationData/TransformationData.h"
#include "../ResourcesData/IndexVertexResourcesData/IndexVertexResourcesData.h"
#include "../ResourcesData/TransformationResourcesDataCBV/TransformationResourcesDataCBV.h"
#include "../ResourcesData/MaterialResourcesDataCBV/MaterialResourcesDataCBV.h"
#include "DirectXBase/DirectXHeap/DirectXHeap.h"

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
	/// インデックスと頂点の
	/// </summary>
	/// <param name="modelIndex"></param>
	void Register(uint32_t modelIndex);

	// モデルデータ
	std::vector<ModelData> modelData_{};

	// ルートノード
	Node rootNode_;

	// モデルハンドル
	uint32_t modelHandle_;

	// ファイルパス
	std::string filePath_;

	// テクスチャハンドル
	std::vector<uint32_t> textureHandle_;


	struct ModelIndex
	{
		// インデックスリソース
		Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;

		// インデックスバッファビュー
		D3D12_INDEX_BUFFER_VIEW indexBufferView_{};

		// インデックスデータ
		uint32_t* indexData_ = nullptr;
	};

	struct ModelVertex
	{
		// 頂点リソース
		Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;

		// 頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};

		// 頂点データ
		VertexDataForGPU* vertexData_ = nullptr;
	};

	std::vector<ModelVertex> modelVertex_;
	std::vector<ModelIndex> modelIndex_;


	
	// アニメーション時間
	float animationTime_ = 0.0f;

	// アニメーション
	Animation animation_{};

	// スケルトン
	Skeleton skeleton_{};

	// スキンクラスター
	std::vector<SkinCluster> skinCluster_{};


private:

	// デバイス
	ID3D12Device* device_;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_;
};


class ModelStore
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static ModelStore* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textureStore"></param>
	void Initialize(TextureStore* textureStore, DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

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

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// インスタンス
	static ModelStore* instance_;

	// シングルトンを使うため、コンストラクタなどは使わない
	ModelStore() = default;
	~ModelStore() = default;
	ModelStore(ModelStore&) = delete;
	ModelStore& operator=(ModelStore&) = delete;


	// 格納されたモデルデータ
	std::vector<std::unique_ptr<ModelInfoDatum>> modelInfoData_;
};

