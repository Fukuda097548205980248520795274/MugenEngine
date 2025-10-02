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
	indexVertexResource_[modelIndex]->Register();
}




/// <summary>
/// 初期化
/// </summary>
/// <param name="textureStore"></param>
void ModelStore::Initialize(TextureStore* textureStore, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(textureStore);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	textureStore_ = textureStore;
	device_ = device;
	commandList_ = commandList;
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

	// ハンドルを取得する
	uint32_t handle = static_cast<uint32_t>(modelInfoData_.size());
	modelInfoDatum->modelHandle_ = handle;
	modelInfoDatum->filePath_ = filePath;

	// モデルデータの数に合わせてデータを作成する
	for (uint32_t modelIndex = 0; modelIndex < modelInfoDatum->modelData_.size(); ++modelIndex)
	{
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


		/*----------------------
		    インデックスと頂点
		----------------------*/

		// 生成と初期化
		std::unique_ptr<IndexVertexResourcesData> indexVertexResource = std::make_unique<IndexVertexResourcesData>();
		indexVertexResource->Initialize(device_, commandList_,
			static_cast<uint32_t>(modelInfoDatum->modelData_[modelIndex].indices.size()),
			static_cast<uint32_t>(modelInfoDatum->modelData_[modelIndex].vertices.size()));

		// インデックスデータを入力する
		std::memcpy(indexVertexResource->indexData_, modelInfoDatum->modelData_[modelIndex].indices.data(),
			sizeof(uint32_t) * modelInfoDatum->modelData_[modelIndex].indices.size());

		// 頂点データを入力する
		std::memcpy(indexVertexResource->vertexData_, modelInfoDatum->modelData_[modelIndex].vertices.data(),
			sizeof(VertexDataForGPU) * modelInfoDatum->modelData_[modelIndex].vertices.size());

		// 登録する
		modelInfoDatum->indexVertexResource_.push_back(std::move(indexVertexResource));
	}


	// 登録する
	modelInfoData_.push_back(std::move(modelInfoDatum));

	return handle;
}