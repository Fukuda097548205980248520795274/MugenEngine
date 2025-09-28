#include "MainCameraResourcesDataCBV.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void MainCameraResourcesDataCBV::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;

	// リソースの生成
	resource_ = CreateBufferResource(device_, sizeof(CameraDataForGPU));

	// データを割り当てる
	resource_->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->worldPosition = Vector3(0.0f, 0.0f, 0.0f);
}

/// <summary>
/// 登録する
/// </summary>
/// <param name="rootParameterIndex"></param>
void MainCameraResourcesDataCBV::Register(UINT rootParameterIndex)
{
	commandList_->SetGraphicsRootConstantBufferView(rootParameterIndex, resource_->GetGPUVirtualAddress());
}