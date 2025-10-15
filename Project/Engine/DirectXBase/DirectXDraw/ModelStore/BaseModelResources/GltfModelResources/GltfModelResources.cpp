#include "GltfModelResources.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device_"></param>
/// <param name="commandList"></param>
void GltfModelResources::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, TextureStore* textureStore,
	const std::string& fileDirectory, const std::string& fileName, const std::string& extName, ModelHandle modelHandle)
{
	// 基底クラスの初期化
	BaseModelResources::Initialize(device, commandList, textureStore, fileDirectory, fileName, extName, modelHandle);


	// モデルデータを取得する
	modelData_ = LoadGltfFileWidthBone(fileDirectory, fileName);

	// ノードを取得する
	rootNode_ = GetReadNode(fileDirectory, fileName, MakeIdentityMatrix4x4());

	// アニメーションのデータを取得する
	animation_ = LoadAnimationFile(fileDirectory, fileName, modelData_);

	// スキニングする（ボーンがある）可能性があるときのみ、スケルトン情報を取得する
	if(modelData_.isSkinning)
		skeleton_ = CreateSkeleton(rootNode_);

	// メッシュデータの数に合わせて生成する
	for (uint32_t i = 0 ; i < modelData_.numMesh ; ++i)
	{
		// 名前を取得する
		std::string meshName = modelData_.meshNames_[i];


		// リソース
		std::pair<ComPtr<ID3D12Resource>, ComPtr<ID3D12Resource>> resource;

		// ビュー
		std::pair<D3D12_INDEX_BUFFER_VIEW, D3D12_VERTEX_BUFFER_VIEW> bufferView;

		// データ
		std::pair<uint32_t*, VertexDataForGPU*> data;

		// スキニングする可能性があるときのみ、スキンクラスターを生成する
		if (modelData_.isSkinning)
		{
			modelData_.meshData[meshName].skinCluster = CreateSkinCluster(device_, skeleton_, modelData_.meshData[meshName], directXHeap_);
		}

		/*------------------------
			テクスチャを読み取る
		------------------------*/

		// テクスチャハンドル
		TextureHandle textureHandle{};

		// テクスチャがないとき
		if (modelData_.meshData[meshName].material.textureFilePath == "")
		{
			// テクスチャを読み込む
			textureHandle = textureStore_->LoadTexture("./Resources/Textures/white2x2.png");
		}
		else
		{
			// テクスチャがあるとき
			textureHandle = textureStore_->LoadTexture(modelData_.meshData[meshName].material.textureFilePath.c_str());
		}


		/*----------------------------------
			インデックスリソースを生成する
		----------------------------------*/

		// リソース生成
		resource.first = CreateBufferResource(device_, sizeof(uint32_t) * modelData_.meshData[meshName].indices.size());

		// ビューの設定
		bufferView.first.BufferLocation = resource.first->GetGPUVirtualAddress();
		bufferView.first.Format = DXGI_FORMAT_R32_UINT;
		bufferView.first.SizeInBytes = sizeof(uint32_t) * static_cast<UINT>(modelData_.meshData[meshName].indices.size());

		// データを割り当てる
		resource.first->Map(0, nullptr, reinterpret_cast<void**>(&data.first));

		// モデルデータの値を持ってくる
		std::memcpy(data.first, modelData_.meshData[meshName].indices.data(),
			sizeof(uint32_t) * static_cast<UINT>(modelData_.meshData[meshName].indices.size()));


		/*-------------------------
			頂点リソースを生成する
		-------------------------*/

		// リソース生成
		resource.second = CreateBufferResource(device_, sizeof(VertexDataForGPU) * modelData_.meshData[meshName].vertices.size());

		// ビューの設定
		bufferView.second.BufferLocation = resource.second->GetGPUVirtualAddress();
		bufferView.second.SizeInBytes = sizeof(VertexDataForGPU) * static_cast<UINT>(modelData_.meshData[meshName].vertices.size());
		bufferView.second.StrideInBytes = sizeof(VertexDataForGPU);

		// データを割り当てる
		resource.second->Map(0, nullptr, reinterpret_cast<void**>(&data.second));

		// モデルデータの値を持ってくる
		std::memcpy(data.second, modelData_.meshData[meshName].vertices.data(),
			sizeof(VertexDataForGPU) * static_cast<UINT>(modelData_.meshData[meshName].vertices.size()));


		/*---------------------
			リストに登録する
		---------------------*/

		textureHandle_.push_back(textureHandle);
		resource_.push_back(resource);
		bufferView_.push_back(bufferView);
		data_.push_back(data);
	}

	return;
}

/// <summary>
/// 頂点とインデックスをコマンドリストに登録する
/// </summary>
/// <param name="meshIndex"></param>
void GltfModelResources::Register(uint32_t meshIndex)
{
	// メッシュの名前を取得する
	std::string meshName = modelData_.meshNames_[meshIndex];

	// スキニング時と処理を変える
	if (modelData_.isSkinning && modelData_.isAnimation)
	{
		// インデックスの設定
		commandList_->IASetIndexBuffer(&bufferView_[meshIndex].first);

		// 頂点の設定
		D3D12_VERTEX_BUFFER_VIEW vbvs[2] = { bufferView_[meshIndex].second, modelData_.meshData[meshName].skinCluster.influenceBufferView };
		commandList_->IASetVertexBuffers(0, 2, vbvs);

		commandList_->SetGraphicsRootDescriptorTable(10, modelData_.meshData[meshName].skinCluster.paletteSrvHandle.second);
	}
	else
	{
		// インデックスの設定
		commandList_->IASetIndexBuffer(&bufferView_[meshIndex].first);

		// 頂点の設定
		commandList_->IASetVertexBuffers(0, 1, &bufferView_[meshIndex].second);
	}
}