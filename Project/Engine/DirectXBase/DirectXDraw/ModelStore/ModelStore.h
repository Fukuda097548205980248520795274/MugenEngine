#pragma once
#include <filesystem>

#include "BaseModelResources/GltfModelResources/GltfModelResources.h"
#include "BaseModelResources/ObjModelResources/ObjModelResources.h"

#include "Func/CreateBufferResource/CreateBufferResource.h"
#include "Func/LoadModel/LoadModel.h"
#include "../TextureStore/TextureStore.h"
#include "../DataForGPU/MaterialData/MaterialData.h"
#include "../DataForGPU/TransformationData/TransformationData.h"
#include "../ResourcesData/IndexVertexResourcesData/IndexVertexResourcesData.h"



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
	void Initialize(TextureStore* textureStore, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap);

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
	BaseModelResources* GetModelInfo(uint32_t modelHandle)const { return modelResources_[modelHandle].get(); }


private:

	// テクスチャストア
	TextureStore* textureStore_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;


	// インスタンス
	static ModelStore* instance_;

	// シングルトンを使うため、コンストラクタなどは使わない
	ModelStore() = default;
	~ModelStore() = default;
	ModelStore(ModelStore&) = delete;
	ModelStore& operator=(ModelStore&) = delete;


	// 格納されたモデルデータ
	std::vector<std::unique_ptr<BaseModelResources>> modelResources_;
};

