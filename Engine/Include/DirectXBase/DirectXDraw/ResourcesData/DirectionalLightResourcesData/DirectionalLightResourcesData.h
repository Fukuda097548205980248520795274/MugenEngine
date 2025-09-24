#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/LightData/LightData.h"

class DirectionalLightResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	/// <param name="rootParameterIndex"></param>
	void Register(UINT rootParameterIndex);


	// ライトデータ
	DirectionalLightForGPU* lightData_ = nullptr;

private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// ライトリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> lightResource_ = nullptr;
};

