#include "DirectionalLightResourcesData.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void DirectionalLightResourcesData::Initialize(DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t numLight)
{
	// nullptrチェック
	assert(directXHeap);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	directXHeap_ = directXHeap;
	device_ = device;
	commandList_ = commandList;
	numLight_ = numLight;


	// ライトリソースの生成
	lightResource_ = CreateBufferResource(device_, sizeof(DirectionalLightForGPU) * numLight_);
	lightResource_->Map(0, nullptr, reinterpret_cast<void**>(&lightData_));

	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Buffer.NumElements = numLight_;
	srvDesc.Buffer.StructureByteStride = sizeof(DirectionalLightForGPU);

	// ハンドルを取得する
	lightCPUHandle_ = directXHeap_->GetSrvCPUDescriptorHandle();
	lightGPUHandle_ = directXHeap_->GetSrvGPUDescriptorHandle();

	device_->CreateShaderResourceView(lightResource_.Get(), &srvDesc, lightCPUHandle_);


	// ライト数リソースの生成
	numLightResource_ = CreateBufferResource(device, sizeof(uint32_t));
	numLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&numLightData_));
	*numLightData_ = 0;
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
/// <param name="rootParameterIndex"></param>
void DirectionalLightResourcesData::Register(UINT lightRootParameterIndex, UINT numLightRootParameterIndex)
{
	// ライトリソースの設定
	commandList_->SetGraphicsRootDescriptorTable(lightRootParameterIndex, lightGPUHandle_);

	// ライト数リソースの設定
	commandList_->SetGraphicsRootConstantBufferView(numLightRootParameterIndex, numLightResource_->GetGPUVirtualAddress());
}