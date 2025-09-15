#include "DirectXDraw.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="commandList"></param>
/// <param name="device"></param>
void DirectXDraw::Initialize(LogFile* logFile, DirectXHeap* directXHeap, const int32_t* kClientWidth, const int32_t* kClientHeight,
	ID3D12GraphicsCommandList* commandList, ID3D12Device* device)
{
	// nullptrチェック
	assert(logFile);
	assert(directXHeap);
	assert(kClientWidth);
	assert(kClientHeight);
	assert(commandList);
	assert(device);

	// 引数を受け取る
	logFile_ = logFile;
	directXHeap_ = directXHeap;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	commandList_ = commandList;
	device_ = device;


	// DirectXシェーダコンパイラの生成と初期化
	directXShaderCompiler_ = std::make_unique<DirectXShaderCompile>();
	directXShaderCompiler_->Initialize(logFile_);


	// プリミティブ用PSOの生成と初期化
	primitivePSO_ = std::make_unique<PSOPrimitive>();
	primitivePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);


	// ビューポートの設定
	viewport_.Width = static_cast<float>(*kClientWidth_);
	viewport_.Height = static_cast<float>(*kClientHeight_);
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;

	// シザー矩形の設定
	scissorRect_.left = 0;
	scissorRect_.right = *kClientWidth_;
	scissorRect_.top = 0;
	scissorRect_.bottom = *kClientHeight_;




	// 三角形用リソースの生成と初期化
	resourcesTriangle_ = std::make_unique<ResourcesTriangle>();
	resourcesTriangle_->Initialize(device_, commandList_);

	// 図形の設定
	transform_.scale = { 1.0f , 1.0f , 1.0f };

	// カメラの設定
	camera_.scale = { 1.0f , 1.0f , 1.0f };
	camera_.translation.z = -5.0f;

	DirectX::ScratchImage mipImages = LoadTexture("./Resources/Textures/uvChecker.png");
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	textureResource_ = CreateTextureResource(device_, metadata);
	subresource_ = UploadTextureData(textureResource_.Get(), mipImages, device_, commandList_);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);

	textureSrvHandleCPU_ = directXHeap_->GetSrvCPUDescriptorHandle();
	textureSrvHandleGPU_ = directXHeap_->GetSrvGPUDescriptorHandle();

	// SRVの生成
	device_->CreateShaderResourceView(textureResource_.Get(), &srvDesc, textureSrvHandleCPU_);
}



/// <summary>
/// 三角形を描画する
/// </summary>
void DirectXDraw::DrawTriangle()
{
	/*------------------
	    座標変換を行う
	------------------*/

	// 回転させる
	transform_.rotation.y += 0.03f;

	// ワールド行列
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform_.scale, transform_.rotation, transform_.translation);

	// ビュー行列
	Matrix4x4 viewMatrix = MakeInverseMatrix(MakeAffineMatrix(camera_.scale, camera_.rotation, camera_.translation));

	// 透視投影行列
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(*kClientWidth_) / float(*kClientHeight_), 0.1f, 100.0f);

	*resourcesTriangle_->transformationData_ = worldMatrix * viewMatrix * projectionMatrix;


	/*---------------------------
	    コマンドリストに登録する
	---------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// リソースの設定
	resourcesTriangle_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureSrvHandleGPU_);

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// ドローコール
	commandList_->DrawInstanced(3, 1, 0, 0);
}