#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>

#include "../../../../Externals/DirectXTex/DirectXTex.h"
#include "../../../../Externals/DirectXTex/d3dx12.h"
#include "../ConvertString/ConvertString.h"
#include "../CreateBufferResource/CreateBufferResource.h"

/// <summary>
/// テクスチャを読み込む
/// </summary>
/// <param name="filePath"></param>
/// <returns></returns>
DirectX::ScratchImage LoadTextureGetMipImages(const std::string& filePath);

/// <summary>
/// テクスチャ用リソースを作成する
/// </summary>
/// <param name="device"></param>
/// <param name="metadata"></param>
/// <returns></returns>
Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

/// <summary>
/// 深度情報テクスチャリソースを作成する
/// </summary>
/// <param name="device"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int height);

/// <summary>
/// テクスチャデータをGPUに転送するためのリソースを生成する
/// </summary>
/// <param name="texture"></param>
/// <param name="mipImages"></param>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <returns></returns>
[[nodiscard]]
Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages,
	ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
