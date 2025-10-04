#include "ModelStore.h"



/// <summary>
/// 初期化
/// </summary>
/// <param name="device_"></param>
/// <param name="commandList"></param>
void ModelInfoDatum::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
}

/// <summary>
/// インデックスと頂点の
/// </summary>
/// <param name="modelIndex"></param>
void ModelInfoDatum::Register(uint32_t modelIndex)
{
	commandList_->IASetIndexBuffer(&modelIndex_[modelIndex].indexBufferView_);

	D3D12_VERTEX_BUFFER_VIEW vbvs[2] = { modelVertex_[modelIndex].vertexBufferView_, skinCluster_[modelIndex].influenceBufferView };
	commandList_->IASetVertexBuffers(0, 2, vbvs);

	commandList_->SetGraphicsRootDescriptorTable(10, skinCluster_[modelIndex].paletteSrvHandle.second);
}



// インスタンスの初期化
ModelStore* ModelStore::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
ModelStore* ModelStore::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ModelStore();
	}

	return instance_;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="textureStore"></param>
void ModelStore::Initialize(TextureStore* textureStore, DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(textureStore);
	assert(device);
	assert(commandList);
	assert(directXHeap);

	// 引数を受け取る
	textureStore_ = textureStore;
	device_ = device;
	commandList_ = commandList;
	directXHeap_ = directXHeap;
}

/// <summary>
/// 終了処理
/// </summary>
void ModelStore::Finalize()
{
	delete instance_;
}

/// <summary>
/// モデルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
uint32_t ModelStore::LoadModel(const std::string& directoryPath, const std::string& filename)
{
	// ファイルパス
	std::string filePath = directoryPath + "/" + filename;

	// 同一のファイルパスがあったら、そのハンドルを返す
	for (std::unique_ptr<ModelInfoDatum>& datum : modelInfoData_)
	{
		if (strcmp(filePath.c_str(), datum->filePath_.c_str()) == 0)
			return datum->modelHandle_;
	}

	// モデルデータを生成する
	std::unique_ptr<ModelInfoDatum> modelInfoDatum = std::make_unique<ModelInfoDatum>();
	modelInfoDatum->Initialize(device_, commandList_);

	// モデルを読み込む
	modelInfoDatum->modelData_ = LoadObjFile(directoryPath, filename);

	// ノード情報を取得する
	modelInfoDatum->rootNode_ = GetReadNode(directoryPath, filename);
	NodeWorldMatrix(modelInfoDatum->rootNode_, MakeIdentityMatrix4x4());

	// アニメーション情報を取得する
	modelInfoDatum->animation_ = LoadAnimationFile(directoryPath, filename);

	// スケルトン情報を取得する
	modelInfoDatum->skeleton_ = CreateSkeleton(modelInfoDatum->rootNode_);

	// ハンドルを取得する
	uint32_t handle = static_cast<uint32_t>(modelInfoData_.size());
	modelInfoDatum->modelHandle_ = handle;
	modelInfoDatum->filePath_ = filePath;

	// モデルデータの数に合わせてデータを作成する
	for (uint32_t modelIndex = 0; modelIndex < modelInfoDatum->modelData_.size(); ++modelIndex)
	{
		/*----------------------------
		    スキンクラスターを生成する
		----------------------------*/

		modelInfoDatum->skinCluster_.push_back(CreateSkinCluster(device_, modelInfoDatum->skeleton_, modelInfoDatum->modelData_[modelIndex], directXHeap_));


		/*---------------
		    テクスチャ
		---------------*/

		// テクスチャハンドル
		uint32_t textureHandle = 0;

		// ファイルパスがなかったら白いテクスチャで代替する
		if (modelInfoDatum->modelData_[modelIndex].material.textureFilePath == "")
		{
			// テクスチャを読み込む
			textureHandle = textureStore_->LoadTexture("./Resources/Textures/white2x2.png");
		} 
		else
		{
			// テクスチャを読み込む
			textureHandle = textureStore_->LoadTexture(modelInfoDatum->modelData_[modelIndex].material.textureFilePath);
		}

		// 登録する
		modelInfoDatum->textureHandle_.push_back(textureHandle);


		/*-----------------------------
			インデックスリソースの準備
		-----------------------------*/

		UINT indexNum = static_cast<UINT>(modelInfoDatum->modelData_[modelIndex].indices.size());

		UINT vertexNum = static_cast<UINT>(modelInfoDatum->modelData_[modelIndex].vertices.size());

		ModelInfoDatum::ModelIndex index;

		// リソース生成
		index.indexResource_ =
			CreateBufferResource(device_, sizeof(uint32_t) * indexNum);

		// ビューの設定
		index.indexBufferView_.BufferLocation = index.indexResource_->GetGPUVirtualAddress();
		index.indexBufferView_.SizeInBytes = sizeof(uint32_t) * indexNum;
		index.indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

		// データを割り当てる
		index.indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&index.indexData_));

		// インデックスデータを入力する
		std::memcpy(index.indexData_, modelInfoDatum->modelData_[modelIndex].indices.data(),
			sizeof(uint32_t) * modelInfoDatum->modelData_[modelIndex].indices.size());

		// 登録する
		modelInfoDatum->modelIndex_.push_back(index);


		/*----------------------
			頂点リソースの準備
		----------------------*/

		ModelInfoDatum::ModelVertex vertex;

		// リソース生成
		vertex.vertexResource_ = CreateBufferResource(device_, sizeof(VertexDataForGPU) * vertexNum);

		// ビューの設定
		vertex.vertexBufferView_.BufferLocation = vertex.vertexResource_->GetGPUVirtualAddress();
		vertex.vertexBufferView_.SizeInBytes = sizeof(VertexDataForGPU) * vertexNum;
		vertex.vertexBufferView_.StrideInBytes = sizeof(VertexDataForGPU);

		// データを割り当てる
		vertex.vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertex.vertexData_));

		// 頂点データを入力する
		std::memcpy(vertex.vertexData_, modelInfoDatum->modelData_[modelIndex].vertices.data(),
			sizeof(VertexDataForGPU)* modelInfoDatum->modelData_[modelIndex].vertices.size());


		// 登録する
		modelInfoDatum->modelVertex_.push_back(vertex);
	}


	// 登録する
	modelInfoData_.push_back(std::move(modelInfoDatum));

	return handle;
}