#include "ModelStore.h"


// インスタンスの初期化
std::unique_ptr<ModelStore> ModelStore::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
ModelStore* ModelStore::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = std::make_unique<ModelStore>();
	}

	return instance_.get();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="textureStore"></param>
void ModelStore::Initialize(TextureStore* textureStore, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap)
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
	instance_.reset();
	instance_ = nullptr;
}

/// <summary>
/// モデルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
ModelHandle ModelStore::LoadModel(const std::string& directoryPath, const std::string& filename)
{
	// ファイルパス
	std::string filePath = directoryPath + "/" + filename;

	// 同一のファイルパスがあったら、そのハンドルを返す
	for (std::unique_ptr<BaseModelResources>& resource : modelResources_)
	{
		// スキニングのモデルは同じパスでもハンドルを返さない
		if (resource->IsSkinning())
			continue;

		if (strcmp(filePath.c_str(), resource->GetFilePath().c_str()) == 0)
			return resource->GetModelHandle();
	}


	// ハンドルを取得する
	ModelHandle handle{};
	handle.value = static_cast<uint32_t>(modelResources_.size());

	// モデルリソースを用意する
	std::unique_ptr<ObjModelResources> objModelResource = nullptr;
	std::unique_ptr<GltfModelResources> gltfModelResource = nullptr;

	// 拡張子を取得する
	std::filesystem::path p(filename);
	std::string extName = p.extension().string();

	// 拡張子に合わせて処理を変える
	// objファイル
	if (extName.find(".obj") == 0)
	{
		// モデルの生成と初期化
		objModelResource = std::make_unique<ObjModelResources>();
		objModelResource->Initialize(device_, commandList_, textureStore_, directoryPath, filename, extName, handle);

		// 登録する
		modelResources_.push_back(std::move(objModelResource));
	}

	// gltfファイル
	if (extName.find(".gltf") == 0)
	{
		// モデルの生成と初期化
		gltfModelResource = std::make_unique<GltfModelResources>();
		gltfModelResource->SetDirectXHeap(directXHeap_);
		gltfModelResource->Initialize(device_, commandList_, textureStore_, directoryPath, filename, extName, handle);

		// 登録する
		modelResources_.push_back(std::move(gltfModelResource));
	}

	return handle;
}