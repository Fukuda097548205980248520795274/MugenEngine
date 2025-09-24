#include "DirectionalLightResourcesData.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void DirectionalLightResourcesData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(device);
	assert(commandList);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;


	// ライトリソースの生成
	lightResource_ = CreateBufferResource(device_, sizeof(DirectionalLightForGPU));
	lightResource_->Map(0, nullptr, reinterpret_cast<void**>(&lightData_));
	lightData_->color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	lightData_->direction = Vector3(0.0f, -1.0f, 0.0f);
	lightData_->intensity = 1.0f;
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
/// <param name="rootParameterIndex"></param>
void DirectionalLightResourcesData::Register(UINT rootParameterIndex)
{
	// ライトリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(rootParameterIndex, lightResource_->GetGPUVirtualAddress());
}