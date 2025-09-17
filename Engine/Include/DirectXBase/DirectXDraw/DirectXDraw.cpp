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

	// 球用リソースの生成と初期化
	resourcesSphere_ = std::make_unique<ResourcesSphere>();
	resourcesSphere_->Initialize(device_, commandList_);

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
/// 球を描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
/// <param name="segment"></param>
/// <param name="ring"></param>
void DirectXDraw::DrawSphere(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle,
	int32_t segment, int32_t ring)
{
	// セグメントとリングの数を制限する
	segment = std::max(segment, resourcesSphere_->GetMinSegment());
	segment = std::min(segment, resourcesSphere_->GetMaxSegment());
	ring = std::max(ring, resourcesSphere_->GetMinRing());
	ring = std::min(ring, resourcesSphere_->GetMaxRing());


	/*-------------------------------
	    インデックスデータを入力する
	-------------------------------*/

	int indexNum = 0;

	for (int32_t latIndex = 0; latIndex < ring; ++latIndex)
	{
		for (int32_t lonIndex = 0; lonIndex < segment; ++lonIndex)
		{
			int startIndex = (latIndex * segment + lonIndex) * 6;
			int index = (latIndex * segment + lonIndex) * 4;

			resourcesSphere_->indexData_[startIndex] = index;
			resourcesSphere_->indexData_[startIndex + 1] = index + 1;
			resourcesSphere_->indexData_[startIndex + 2] = index + 2;
			resourcesSphere_->indexData_[startIndex + 3] = index + 1;
			resourcesSphere_->indexData_[startIndex + 4] = index + 3;
			resourcesSphere_->indexData_[startIndex + 5] = index + 2;

			indexNum += 6;
		}
	}


	/*------------------------
	    頂点データを入力する
	------------------------*/

	float kLonEvery = std::numbers::pi_v<float> *2.0f / float(segment);
	float kLatEvery = std::numbers::pi_v<float> / float(ring);

	for (int32_t latIndex = 0; latIndex < ring; ++latIndex)
	{
		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;

		for (int32_t lonIndex = 0; lonIndex < segment; ++lonIndex)
		{
			float lon = kLonEvery * lonIndex;

			int startIndex = (latIndex * segment + lonIndex) * 4;

			resourcesSphere_->vertexData_[startIndex].position.x = std::cos(lat) * std::cos(lon);
			resourcesSphere_->vertexData_[startIndex].position.y = std::sin(lat);
			resourcesSphere_->vertexData_[startIndex].position.z = std::cos(lat) * std::sin(lon);
			resourcesSphere_->vertexData_[startIndex].position.w = 1.0f;
			resourcesSphere_->vertexData_[startIndex].texcoord.x = float(lonIndex) / float(segment);
			resourcesSphere_->vertexData_[startIndex].texcoord.y = 1.0f - (float(latIndex) / float(ring));

			resourcesSphere_->vertexData_[startIndex + 1].position.x = std::cos(lat + kLatEvery) * std::cos(lon);
			resourcesSphere_->vertexData_[startIndex + 1].position.y = std::sin(lat + kLatEvery);
			resourcesSphere_->vertexData_[startIndex + 1].position.z = std::cos(lat + kLatEvery) * std::sin(lon);
			resourcesSphere_->vertexData_[startIndex + 1].position.w = 1.0f;
			resourcesSphere_->vertexData_[startIndex + 1].texcoord.x = float(lonIndex) / float(segment);
			resourcesSphere_->vertexData_[startIndex + 1].texcoord.y = 1.0f - (float(latIndex + 1) / float(ring));

			resourcesSphere_->vertexData_[startIndex + 2].position.x = std::cos(lat) * std::cos(lon + kLonEvery);
			resourcesSphere_->vertexData_[startIndex + 2].position.y = std::sin(lat);
			resourcesSphere_->vertexData_[startIndex + 2].position.z = std::cos(lat) * std::sin(lon + kLonEvery);
			resourcesSphere_->vertexData_[startIndex + 2].position.w = 1.0f;
			resourcesSphere_->vertexData_[startIndex + 2].texcoord.x = float(lonIndex + 1) / float(segment);
			resourcesSphere_->vertexData_[startIndex + 2].texcoord.y = 1.0f - (float(latIndex) / float(ring));

			resourcesSphere_->vertexData_[startIndex + 3].position.x = std::cos(lat + kLatEvery) * std::cos(lon + kLonEvery);
			resourcesSphere_->vertexData_[startIndex + 3].position.y = std::sin(lat + kLatEvery);
			resourcesSphere_->vertexData_[startIndex + 3].position.z = std::cos(lat + kLatEvery) * std::sin(lon + kLonEvery);
			resourcesSphere_->vertexData_[startIndex + 3].position.w = 1.0f;
			resourcesSphere_->vertexData_[startIndex + 3].texcoord.x = float(lonIndex + 1) / float(segment);
			resourcesSphere_->vertexData_[startIndex + 3].texcoord.y = 1.0f - (float(latIndex + 1) / float(ring));
		}
	}


	/*------------------
	    座標変換の行列
	------------------*/

	// 座標変換行列を取得する
	*resourcesSphere_->transformationData_ = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*----------------------------
	    コマンドリストに設定する
	----------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// リソースの設定
	resourcesSphere_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(indexNum, 1, 0, 0, 0);
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