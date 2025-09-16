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


	// 図形1の設定
	transform1_.scale = { 1.0f , 1.0f , 1.0f };

	// カメラの設定
	camera3d_.scale = { 1.0f , 1.0f , 1.0f };
	camera3d_.translation.z = -5.0f;


	// 図形2の設定
	transform2_.scale = { 1.0f , 1.0f , 1.0f };
}



/// <summary>
/// 三角形を描画する
/// </summary>
void DirectXDraw::DrawTriangle(uint32_t textureHandle)
{
	/*------------------
	    座標変換を行う
	------------------*/

	// 回転させる
	transform1_.rotation.y += 0.03f;

	// ワールド行列
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform1_.scale, transform1_.rotation, transform1_.translation);

	// ビュー行列
	Matrix4x4 viewMatrix = MakeInverseMatrix(MakeAffineMatrix(camera3d_.scale, camera3d_.rotation, camera3d_.translation));

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
void DirectXDraw::DrawSprite(uint32_t textureHandle)
{
	/*------------------
		座標変換を行う
	------------------*/

	// ワールド行列
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform2_.scale, transform2_.rotation, transform2_.translation);

	// ビュー行列
	Matrix4x4 viewMatrix = MakeIdentityMatrix();

	// 透視投影行列
	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, static_cast<float>(*kClientWidth_), static_cast<float>(*kClientHeight_), 0.0f, 100.0f);

	*resourceSprite_->transformationData_ = worldMatrix * viewMatrix * projectionMatrix;


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