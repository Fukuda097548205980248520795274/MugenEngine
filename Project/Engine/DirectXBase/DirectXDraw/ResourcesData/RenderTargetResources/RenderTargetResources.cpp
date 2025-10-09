#include "RenderTargetResources.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="directXBuffering"></param>
/// <param name="directXHeap"></param>
void RenderTargetResources::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(directXBuffering);
	assert(directXHeap);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	directXBuffering_ = directXBuffering;
	directXHeap_ = directXHeap;


	// クリア最適値を設定する
	clearColor_ = Vector4(0.1f, 0.1f, 0.1f, 0.0f);

	// リソースを生成する
	resource_ = CreateRenderTextureResource(device_, directXBuffering_->GetSwapChainDesc().Width, directXBuffering_->GetSwapChainDesc().Height,
		directXBuffering_->GetSwapChainDesc().Format, directXBuffering_->GetRtvDesc().Format, clearColor_);

	/*----------------
	    RTVの設定
	----------------*/

	// スワップチェーンのRTV設定を反映させる
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = directXBuffering_->GetRtvDesc().Format;
	rtvDesc.ViewDimension = directXBuffering_->GetRtvDesc().ViewDimension;
	rtvDesc.Texture2D.MipSlice = 0;
	rtvDesc.Texture2D.PlaneSlice = 0;

	// ディスクリプタハンドルを取得する
	rtvDescriptorHandle_ = directXHeap_->GetRtvCPUDescriptorHandle();

	device_->CreateRenderTargetView(resource_.Get(), &rtvDesc, rtvDescriptorHandle_);



	/*---------------
	    SRVの設定
	---------------*/

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = directXBuffering_->GetRtvDesc().Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.PlaneSlice = 0;

	// ディスクリプタハンドルを取得する
	srvDescriptorHandle_.first = directXHeap_->GetSrvCPUDescriptorHandle();
	srvDescriptorHandle_.second = directXHeap_->GetSrvGPUDescriptorHandle();

	device_->CreateShaderResourceView(resource_.Get(), &srvDesc, srvDescriptorHandle_.first);
}

/// <summary>
/// クリア処理
/// </summary>
void RenderTargetResources::Clear(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
	// レンダーターゲットの設定
	commandList_->OMSetRenderTargets(1, &rtvDescriptorHandle_, false, &dsvHandle);

	// レンダーターゲットをクリアする
	float clearColor[] = { clearColor_.x, clearColor_.y , clearColor_.z , clearColor_.w };
	commandList_->ClearRenderTargetView(rtvDescriptorHandle_, clearColor, 0, nullptr);

	// デプスステンシルをクリアする
	commandList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


}

/// <summary>
/// コマンドリストに登録する
/// </summary>
void RenderTargetResources::Register(UINT textureRootParameterIndex)
{
	commandList_->SetGraphicsRootDescriptorTable(textureRootParameterIndex, srvDescriptorHandle_.second);
}