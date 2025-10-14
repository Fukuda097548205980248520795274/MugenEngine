#pragma once
#include <filesystem>

#include "BaseModelResources/GltfModelResources/GltfModelResources.h"
#include "BaseModelResources/ObjModelResources/ObjModelResources.h"

#include "Func/CreateBufferResource/CreateBufferResource.h"
#include "Func/LoadModel/LoadModel.h"
#include "../TextureStore/TextureStore.h"
#include "../DataForGPU/MaterialData/MaterialData.h"
#include "../DataForGPU/TransformationData/TransformationData.h"
#include "Handle/Handle.h"



class ModelStore
{
public:

	~ModelStore() = default;

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
	ModelHandle LoadModel(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// モデルの情報のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	BaseModelResources* GetModelInfo(ModelHandle handle)const { return modelResources_[handle.value].get(); }

	/// <summary>
	/// メッシュ数のGetter
	/// </summary>
	/// <param name="handle"></param>
	/// <returns></returns>
	uint32_t GetNumMesh(ModelHandle handle)const { return static_cast<uint32_t>(modelResources_[handle.value]->GetModelData().meshData.size()); }

	/// <summary>
	/// アニメーションフラグのGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	bool IsAnimation(ModelHandle handle)const { return modelResources_[handle.value]->IsAnimation(); }

	/// <summary>
	/// アニメーション時間のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	float GetAnimationDuration(ModelHandle handle)const { return modelResources_[handle.value]->GetAnimation().duration; }

	/// <summary>
	/// メッシュ番号を取得する
	/// </summary>
	/// <param name="handle"></param>
	/// <param name="meshName"></param>
	/// <returns></returns>
	uint32_t GetMeshNumber(ModelHandle handle, const std::string& meshName);


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
	static std::unique_ptr<ModelStore> instance_;

	// フレンド宣言
	friend std::unique_ptr<ModelStore> std::make_unique<ModelStore>();


	// シングルトンを使うため、コンストラクタなどは使わない
	ModelStore() = default;
	ModelStore(ModelStore&) = delete;
	ModelStore& operator=(ModelStore&) = delete;


	// 格納されたモデルデータ
	std::vector<std::unique_ptr<BaseModelResources>> modelResources_;
};

