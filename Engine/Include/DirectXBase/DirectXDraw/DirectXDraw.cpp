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

	// テクスチャ格納場所の生成と初期化
	textureStore_ = std::make_unique<TextureStore>();
	textureStore_->Initialize(directXHeap_, device_, commandList_);


	// プリミティブ用PSOの生成と初期化
	primitivePSO_ = std::make_unique<OrganizePSOPrimitive>();
	primitivePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);

	// スプライト用PSOの生成と初期化
	spritePSO_ = std::make_unique<OrganizePSOSprite>();
	spritePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);


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

	// スプライト用リソースの生成と初期化
	resourceSprite_ = std::make_unique<ResourcesSprite>();
	resourceSprite_->Initialize(device_, commandList_);
}



/// <summary>
/// 三角形を描画する
/// </summary>
void DirectXDraw::DrawTriangle(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle)
{
	/*------------------
	    座標変換を行う
	------------------*/

	// 座標変換行列を入力する
	*resourcesTriangle_->transformationData_ = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


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
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// ドローコール
	commandList_->DrawInstanced(6, 1, 0, 0);
}

/// <summary>
/// スプライトを描画する
/// </summary>
/// <param name="textureHandle"></param>
void DirectXDraw::DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle)
{
	/*------------------
		座標変換を行う
	------------------*/

	// 座標変換行列を入力する
	*resourceSprite_->transformationData_ = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*---------------------------
		コマンドリストに登録する
	---------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	spritePSO_->SetPSOState();

	// リソースの設定
	resourceSprite_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawInstanced(6, 1, 0, 0);
}