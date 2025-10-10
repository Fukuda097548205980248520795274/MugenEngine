#include "TransformationResourceDataInstancing.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <param name="numMaxInstance">最大インスタンス数</param>
void TransformationResourceDataInstancing::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap, uint32_t numMaxInstance)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(directXHeap);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	directXHeap_ = directXHeap;
	numMaxInstance_ = numMaxInstance;


	/*----------------------
	    リソースを作成する
	----------------------*/

	// リソース生成
	resource_ = CreateBufferResource(device_, sizeof(TransformationDataForGPU) * numMaxInstance_);

	// データを割り当てる
	resource_->Map(0, nullptr, reinterpret_cast<void**>(&data_));

	// データを初期化する
	for (uint32_t i = 0; i < numMaxInstance_; ++i)
	{
		data_[i].world = MakeIdentityMatrix4x4();
		data_[i].worldInverseTranspose = MakeIdentityMatrix4x4();
		data_[i].worldViewProjection = MakeIdentityMatrix4x4();
	}


	/*----------------
	    SRVの設定
	----------------*/

	// srvの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Buffer.NumElements = numMaxInstance_;
	srvDesc.Buffer.StructureByteStride = sizeof(TransformationDataForGPU);

	// ディスクリプタハンドルを取得する
	srvDescriptorHandle_.first = directXHeap_->GetSrvCPUDescriptorHandle();
	srvDescriptorHandle_.second = directXHeap_->GetSrvGPUDescriptorHandle();

	device_->CreateShaderResourceView(resource_.Get(), &srvDesc, srvDescriptorHandle_.first);
}


/// <summary>
/// コマンドリストに登録する
/// </summary>
/// <param name="transformationRootParameter"></param>
void TransformationResourceDataInstancing::Register(UINT transformationRootParameter)
{
	commandList_->SetGraphicsRootDescriptorTable(transformationRootParameter, srvDescriptorHandle_.second);
}