#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/CameraDataForGPU/CameraDataForGPU.h"

class MainCameraResourcesDataCBV
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 登録する
	/// </summary>
	/// <param name="rootParameterIndex"></param>
	void Register(UINT rootParameterIndex);


	// データ
	CameraDataForGPU* data_ = nullptr;

private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_ = nullptr;
};

