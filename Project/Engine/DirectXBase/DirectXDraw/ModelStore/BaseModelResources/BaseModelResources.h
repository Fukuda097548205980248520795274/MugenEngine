#pragma once
#include "Func/CreateBufferResource/CreateBufferResource.h"
#include "Func/LoadModel/LoadModel.h"
#include "../../TextureStore/TextureStore.h"
#include "DirectXBase/DirectXDraw/TextureStore/TextureStore.h"

class BaseModelResources
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device_"></param>
	/// <param name="commandList"></param>
	virtual void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, TextureStore* textureStore,
		const std::string& fileDirectory, const std::string& fileName, const std::string& extName , uint32_t modelHandle);

	/// <summary>
	/// インデックスと頂点の
	/// </summary>
	/// <param name="meshIndex"></param>
	virtual void Register(uint32_t meshIndex) = 0;

	/// <summary>
	/// ファイルパスのGetter
	/// </summary>
	/// <returns></returns>
	std::string GetFilePath()const { return filePath_; }

	/// <summary>
	/// 拡張子名のGetter
	/// </summary>
	/// <returns></returns>
	std::string GetExtName()const { return extName_; }

	/// <summary>
	/// モデルハンドルのGetter
	/// </summary>
	/// <returns></returns>
	uint32_t GetModelHandle()const { return modelHandle_; }

	/// <summary>
	/// モデルデータのGetter
	/// </summary>
	/// <returns></returns>
	ModelData GetModelData()const { return modelData_; }

	/// <summary>
	/// テクスチャハンドルのGetter
	/// </summary>
	/// <param name="meshIndex"></param>
	/// <returns></returns>
	uint32_t GetTextureHandle(uint32_t meshIndex)const { return textureHandle_[meshIndex]; }

	/// <summary>
	/// ルートノードのGetter
	/// </summary>
	/// <returns></returns>
	virtual Node GetRootNode()const = 0;

	/// <summary>
	/// アニメーションフラグのGetter
	/// </summary>
	/// <returns></returns>
	bool IsAnimation()const { return modelData_.isAnimation; }

	/// <summary>
	/// スキニングフラグのGetter
	/// </summary>
	/// <returns></returns>
	bool IsSkinning()const { return modelData_.isSkinning; }

	/// <summary>
	/// メッシュ数の
	/// </summary>
	/// <returns></returns>
	uint32_t GetNumMesh()const { return static_cast<uint32_t>(modelData_.meshData.size()); }

	/// <summary>
	/// インデックス数のGetter
	/// </summary>
	/// <param name="meshIndex"></param>
	/// <returns></returns>
	UINT GetNumIndex(uint32_t meshIndex)const { return static_cast<UINT>(modelData_.meshData[meshIndex].indices.size()); }


	// Microsoft::WRL 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


protected:

	// デバイス
	ID3D12Device* device_;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_;

	// テクスチャ格納場所
	TextureStore* textureStore_ = nullptr;
	




	// モデルデータ
	ModelData modelData_{};


	// ファイルパス
	std::string filePath_;

	// 拡張子名
	std::string extName_;


	// モデルハンドル
	uint32_t modelHandle_;

	// テクスチャハンドル
	std::vector<uint32_t> textureHandle_;


	// リソース
	std::vector<std::pair<ComPtr<ID3D12Resource>, ComPtr<ID3D12Resource>>> resource_;

	// バッファビュー
	std::vector<std::pair<D3D12_INDEX_BUFFER_VIEW, D3D12_VERTEX_BUFFER_VIEW>> bufferView_;

	// データ
	std::vector<std::pair<uint32_t*, VertexDataForGPU*>> data_;
};

