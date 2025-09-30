#include "TransformationResourcesDataCBV.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void TransformationResourcesDataCBV::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptr
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;

	// リソースを生成する
	resource_ = CreateBufferResource(device_, sizeof(TransformationDataForGPU));

	// データを割り当てる
	resource_->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->world = MakeIdentityMatrix4x4();
	data_->worldInverseTranspose = MakeIdentityMatrix4x4();
	data_->worldViewProjection = MakeIdentityMatrix4x4();
}

/// <summary>
/// 登録する
/// </summary>
/// <param name="rootPrameterIndex"></param>
void TransformationResourcesDataCBV::Register(UINT rootPrameterIndex)
{
	commandList_->SetGraphicsRootConstantBufferView(rootPrameterIndex, resource_->GetGPUVirtualAddress());
}