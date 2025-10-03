#pragma once
#include <functional>

#include "../../../Func/LoadTexture/LoadTexture.h"
#include "../../../LogFile/LogFile.h"
#include "../../DirectXHeap/DirectXHeap.h"

class TextureStore
{
public:

	/// <summary>
	/// シングルトンインスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static TextureStore* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXHeap"></param>
	void Initialize(DirectXHeap* directXHeap, LogFile* logFile, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath);

	/// <summary>
	/// GPUハンドルのGetter
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t textureHandle)const { return dataCollection_[textureHandle]->gpuHandle_; }

	/// <summary>
	/// テクスチャのハッシュ値を計算する
	/// </summary>
	/// <param name="image"></param>
	/// <returns></returns>
	size_t CalculateTextureHash(const DirectX::Image& image);


private:

	// 静的メンバ変数のポインタ
	static TextureStore* instance;

	// シングルトンを使うため、コンストラクタなどを使えないようにする
	TextureStore() = default;
	~TextureStore() = default;
	TextureStore(TextureStore&) = delete;
	TextureStore& operator=(TextureStore&) = delete;


	//  DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// ログファイル
	LogFile* logFile_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;



	// テクスチャデータ
	class TextureData
	{
	public:

		// テクスチャリソース
		Microsoft::WRL::ComPtr<ID3D12Resource> textureResource_ = nullptr;

		// 中間リソース
		Microsoft::WRL::ComPtr<ID3D12Resource> subresource_ = nullptr;

		// ミップイメージ
		DirectX::ScratchImage mipImages_{};

		// CPUハンドル
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_{};

		// GPUハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};

		// ハンドル
		uint32_t handle_ = 0;
	};

	// テクスチャデータの集まり
	std::vector<std::unique_ptr<TextureData>> dataCollection_;
};

