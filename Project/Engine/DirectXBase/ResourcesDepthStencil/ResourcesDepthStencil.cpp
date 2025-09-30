#include "ResourcesDepthStencil.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="directXHeap"></param>
void ResourcesDepthStencil::Initialize(DirectXHeap* directXHeap, ID3D12Device* device, const int32_t* kClientWidth, const int32_t* kClientHeight)
{
	// nullptrチェック
	assert(directXHeap);
	assert(device);
	assert(kClientWidth);
	assert(kClientHeight);

	// 引数を受け取る
	directXHeap_ = directXHeap;
	device_ = device;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;


	// 深度情報リソースを作成する
	depthStencilResource_ = CreateDepthStencilTextureResource(device_, *kClientWidth_, *kClientHeight_);


	/*---------------
	    DSVの設定
	---------------*/

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	// CPUハンドルを取得する
	cpuHandle_ = directXHeap_->GetDsvCPUDescriptorHandle();

	// ヒープの先頭にDSVを作る
	device_->CreateDepthStencilView(depthStencilResource_.Get(), &dsvDesc, cpuHandle_);
}