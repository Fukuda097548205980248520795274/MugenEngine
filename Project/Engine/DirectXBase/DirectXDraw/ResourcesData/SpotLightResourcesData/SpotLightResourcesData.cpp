#include "SpotLightResourcesData.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="directXHeap"></param>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <param name="numLight"></param>
void SpotLightResourcesData::Initialize(DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t numLight)
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


	/*------------------------
	    ライトリソースの準備
	------------------------*/

	// リソース生成
	lightResource_ = CreateBufferResource(device_, sizeof(SpotLightForGPU) * numLight_);

	// データを割り当てる
	lightResource_->Map(0, nullptr, reinterpret_cast<void**>(&lightData_));
	
	// SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Buffer.NumElements = numLight_;
	srvDesc.Buffer.StructureByteStride = sizeof(SpotLightForGPU);

	// ハンドルを取得する
	cpuHandle_ = directXHeap_->GetSrvCPUDescriptorHandle();
	gpuHandle_ = directXHeap_->GetSrvGPUDescriptorHandle();

	device_->CreateShaderResourceView(lightResource_.Get(), &srvDesc, cpuHandle_);


	/*-------------------------
	    ライト数リソースの準備
	-------------------------*/

	// リソース生成
	numLightResource_ = CreateBufferResource(device_, sizeof(uint32_t));

	// データを割り当てる
	numLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&numLightData_));
	*numLightData_ = 0;
}

/// <summary>
/// 登録する
/// </summary>
/// <param name="lightRootParameterIndex"></param>
/// <param name="numLightRootParameterIndex"></param>
void SpotLightResourcesData::Register(UINT lightRootParameterIndex, UINT numLightRootParameterIndex)
{
	// ライトの設定
	commandList_->SetGraphicsRootDescriptorTable(lightRootParameterIndex, gpuHandle_);

	// ライト数の設定
	commandList_->SetGraphicsRootConstantBufferView(numLightRootParameterIndex, numLightResource_->GetGPUVirtualAddress());
}