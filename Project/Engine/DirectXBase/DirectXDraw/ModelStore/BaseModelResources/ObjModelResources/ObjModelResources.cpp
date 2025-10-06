#include "ObjModelResources.h"


/// <summary>
/// 初期化
/// </summary>
/// <param name="device_"></param>
/// <param name="commandList"></param>
void ObjModelResources::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, TextureStore* textureStore,
	const std::string& fileDirectory, const std::string& fileName, const std::string& extName, uint32_t modelHandle)
{
	// 基底クラスの初期化
	BaseModelResources::Initialize(device, commandList, textureStore, fileDirectory, fileName, extName, modelHandle);


	// モデルデータを取得する
	modelData_ = LoadObjFile(fileDirectory, fileName);


	// メッシュデータの数に合わせて生成する
	for (MeshData meshDatum : modelData_.meshData)
	{
		// リソース
		std::pair<ComPtr<ID3D12Resource>, ComPtr<ID3D12Resource>> resource;

		// ビュー
		std::pair<D3D12_INDEX_BUFFER_VIEW, D3D12_VERTEX_BUFFER_VIEW> bufferView;

		// データ
		std::pair<uint32_t*, VertexDataForGPU*> data;


		/*------------------------
			テクスチャを読み取る
		------------------------*/

		// テクスチャハンドル
		uint32_t textureHandle = 0;

		// テクスチャがないとき
		if (meshDatum.material.textureFilePath == "")
		{
			// テクスチャを読み込む
			textureHandle = textureStore_->LoadTexture("./Resources/Textures/white2x2.png");
		} else
		{
			// テクスチャがあるとき
			textureHandle = textureStore_->LoadTexture(meshDatum.material.textureFilePath.c_str());
		}


		/*----------------------------------
			インデックスリソースを生成する
		----------------------------------*/

		// リソース生成
		resource.first = CreateBufferResource(device_, sizeof(uint32_t) * meshDatum.indices.size());

		// ビューの設定
		bufferView.first.BufferLocation = resource.first->GetGPUVirtualAddress();
		bufferView.first.Format = DXGI_FORMAT_R32_UINT;
		bufferView.first.SizeInBytes = sizeof(uint32_t) * static_cast<UINT>(meshDatum.indices.size());

		// データを割り当てる
		resource.first->Map(0, nullptr, reinterpret_cast<void**>(&data.first));

		// モデルデータの値を持ってくる
		std::memcpy(data.first, meshDatum.indices.data(), sizeof(uint32_t) * static_cast<UINT>(meshDatum.indices.size()));


		/*-------------------------
			頂点リソースを生成する
		-------------------------*/

		// リソース生成
		resource.second = CreateBufferResource(device_, sizeof(VertexDataForGPU) * meshDatum.vertices.size());

		// ビューの設定
		bufferView.second.BufferLocation = resource.second->GetGPUVirtualAddress();
		bufferView.second.SizeInBytes = sizeof(VertexDataForGPU) * static_cast<UINT>(meshDatum.vertices.size());
		bufferView.second.StrideInBytes = sizeof(VertexDataForGPU);

		// データを割り当てる
		resource.second->Map(0, nullptr, reinterpret_cast<void**>(&data.second));

		// モデルデータの値を持ってくる
		std::memcpy(data.second, meshDatum.vertices.data(), sizeof(VertexDataForGPU) * static_cast<UINT>(meshDatum.vertices.size()));


		/*---------------------
			リストに登録する
		---------------------*/

		textureHandle_.push_back(textureHandle);
		resource_.push_back(resource);
		bufferView_.push_back(bufferView);
		data_.push_back(data);
	}
}

/// <summary>
/// 頂点とインデックスをコマンドリストに登録する
/// </summary>
/// <param name="meshIndex"></param>
void ObjModelResources::Register(uint32_t meshIndex)
{
	// インデックスの設定
	commandList_->IASetIndexBuffer(&bufferView_[meshIndex].first);

	// 頂点の設定
	commandList_->IASetVertexBuffers(0, 1, &bufferView_[meshIndex].second);
}