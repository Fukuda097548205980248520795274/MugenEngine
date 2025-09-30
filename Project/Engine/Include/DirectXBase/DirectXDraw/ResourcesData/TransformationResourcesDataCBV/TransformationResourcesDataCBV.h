#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/TransformationData/TransformationData.h"

class TransformationResourcesDataCBV
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
	/// <param name="rootPrameterIndex"></param>
	void Register(UINT rootPrameterIndex);

	// データ
	TransformationDataForGPU* data_ = nullptr;


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_ = nullptr;
};

