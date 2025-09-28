#include "MaterialResourcesDataCBV.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void MaterialResourcesDataCBV::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptr
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;

	// リソースを生成する
	resource_ = CreateBufferResource(device_, sizeof(MaterialDataForGPU));

	// データを割り当てる
	resource_->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	data_->uvTransform_ = MakeIdentityMatrix4x4();
	data_->enableLighting_ = true;
	data_->enableHalfLambert_ = false;
	data_->enableSpecular_ = true;
	data_->shininess_ = 15.0f;
}

/// <summary>
/// 登録する
/// </summary>
/// <param name="rootParameterIndex"></param>
void MaterialResourcesDataCBV::Register(UINT rootParameterIndex)
{
	commandList_->SetGraphicsRootConstantBufferView(rootParameterIndex, resource_->GetGPUVirtualAddress());
}