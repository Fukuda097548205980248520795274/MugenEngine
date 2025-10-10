#include "TextureStore.h"

// インスタンス
TextureStore* TextureStore::instance = nullptr;

/// <summary>
/// シングルトンインスタンスを取得する
/// </summary>
/// <returns></returns>
TextureStore* TextureStore::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureStore();
	}

	return instance;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="directXHeap"></param>
void TextureStore::Initialize(DirectXHeap* directXHeap, LogFile* logFile, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(directXHeap);
	assert(logFile);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	directXHeap_ = directXHeap;
	logFile_ = logFile;
	device_ = device;
	commandList_ = commandList;
}

/// <summary>
/// 終了処理
/// </summary>
void TextureStore::Finalize()
{
	delete instance;
}

/// <summary>
/// テクスチャを読み込む
/// </summary>
/// <param name="filePath"></param>
/// <returns></returns>
TextureHandle TextureStore::LoadTexture(const std::string& filePath)
{
	// テクスチャデータ
	std::unique_ptr<TextureData> textureData = nullptr;
	textureData = std::make_unique<TextureData>();

	// ミップイメージを取得する
	textureData->mipImages_ = LoadTextureGetMipImages(filePath);

	// ハッシュ値を取得する
	const DirectX::Image* image1 = textureData->mipImages_.GetImages();
	size_t hash1 = CalculateTextureHash(*image1);

	// 過去に取得したミップイメージと被っているかどうかを判断する
	for (std::unique_ptr<TextureData>& data : dataCollection_)
	{
		const DirectX::Image* image2 = data->mipImages_.GetImages();
		size_t hash2 = CalculateTextureHash(*image2);

		if (hash1 == hash2)
		{
			return data->handle_;
		}
	}

	// テクスチャリソースを取得する
	const DirectX::TexMetadata& metadata = textureData->mipImages_.GetMetadata();
	textureData->textureResource_ = CreateTextureResource(device_, metadata);

	// 中間リソースを取得する
	textureData->subresource_ = UploadTextureData(textureData->textureResource_.Get(), textureData->mipImages_, device_, commandList_);

	// SRVを設定する
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);

	// CPU・GPUハンドルを取得する
	textureData->cpuHandle_ = directXHeap_->GetSrvCPUDescriptorHandle();
	textureData->gpuHandle_ = directXHeap_->GetSrvGPUDescriptorHandle();

	// テクスチャリソースにSRVの設定を付与する
	device_->CreateShaderResourceView(textureData->textureResource_.Get(), &srvDesc, textureData->cpuHandle_);

	// ハンドルを取得する
	TextureHandle handle{};
	handle.value = static_cast<uint32_t>(dataCollection_.size());
	textureData->handle_ = handle;

	// 登録する
	dataCollection_.push_back(std::move(textureData));

	return handle;
}

/// <summary>
/// テクスチャのハッシュ値を計算する
/// </summary>
/// <param name="image"></param>
/// <returns></returns>
size_t TextureStore::CalculateTextureHash(const DirectX::Image& image)
{
	size_t hash = 0;
	const uint8_t* data = image.pixels;
	for (size_t i = 0; i < image.slicePitch; ++i)
	{
		hash = (hash * 31) + data[i];
	}
	return hash;
}