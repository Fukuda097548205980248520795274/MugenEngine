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
	textureStore_->Initialize(directXHeap_, logFile_, device_, commandList_);

	// パーティクル格納場所の生成と初期化
	particleStore_ = std::make_unique<ParticleStore>();
	particleStore_->Initialize(this, directXHeap_, device_, commandList_);


	// プリミティブ用PSOの生成と初期化
	primitivePSO_ = std::make_unique<OrganizePSOPrimitive>();
	primitivePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);

	// パーティクル用PSO生成と初期化
	particlePSO_ = std::make_unique<OrganizePSOParticle>();
	particlePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);


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





	// 球用リソースの生成と初期化
	resourcesUVSphere_ = std::make_unique<ResourcesUVSphere>();
	resourcesUVSphere_->Initialize(device_, commandList_);

	// 立方体用リソースの生成と初期化
	resourcesCube_ = std::make_unique<ResourcesCube>();
	resourcesCube_->Initialize(device_, commandList_);

	// スプライト用リソースの生成と初期化
	resourceSprite_ = std::make_unique<ResourcesSprite>();
	resourceSprite_->Initialize(device_, commandList_);
}

/// <summary>
/// ブレンドモードをリセットする
/// </summary>
void DirectXDraw::ResetBlendMode()
{
	primitivePSO_->ResetBlendMode();
}


#pragma region プリミティブ描画処理

/// <summary>
/// UV球を描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
/// <param name="segment"></param>
/// <param name="ring"></param>
void DirectXDraw::DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
	const Vector4& color, bool enableLighting, bool enableHalfLanbert, int32_t segment, int32_t ring)
{
	// セグメントとリングの数を制限する
	segment = std::max(segment, resourcesUVSphere_->GetMinSegment());
	segment = std::min(segment, resourcesUVSphere_->GetMaxSegment());
	ring = std::max(ring, resourcesUVSphere_->GetMinRing());
	ring = std::min(ring, resourcesUVSphere_->GetMaxRing());


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

			resourcesUVSphere_->indexData_[startIndex] = index;
			resourcesUVSphere_->indexData_[startIndex + 1] = index + 1;
			resourcesUVSphere_->indexData_[startIndex + 2] = index + 2;
			resourcesUVSphere_->indexData_[startIndex + 3] = index + 1;
			resourcesUVSphere_->indexData_[startIndex + 4] = index + 3;
			resourcesUVSphere_->indexData_[startIndex + 5] = index + 2;

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

			resourcesUVSphere_->vertexData_[startIndex].position.x = std::cos(lat) * std::cos(lon);
			resourcesUVSphere_->vertexData_[startIndex].position.y = std::sin(lat);
			resourcesUVSphere_->vertexData_[startIndex].position.z = std::cos(lat) * std::sin(lon);
			resourcesUVSphere_->vertexData_[startIndex].position.w = 1.0f;
			resourcesUVSphere_->vertexData_[startIndex].texcoord.x = float(lonIndex) / float(segment);
			resourcesUVSphere_->vertexData_[startIndex].texcoord.y = 1.0f - (float(latIndex) / float(ring));
			resourcesUVSphere_->vertexData_[startIndex].normal.x = resourcesUVSphere_->vertexData_[startIndex].position.x;
			resourcesUVSphere_->vertexData_[startIndex].normal.y = resourcesUVSphere_->vertexData_[startIndex].position.y;
			resourcesUVSphere_->vertexData_[startIndex].normal.z = resourcesUVSphere_->vertexData_[startIndex].position.z;

			resourcesUVSphere_->vertexData_[startIndex + 1].position.x = std::cos(lat + kLatEvery) * std::cos(lon);
			resourcesUVSphere_->vertexData_[startIndex + 1].position.y = std::sin(lat + kLatEvery);
			resourcesUVSphere_->vertexData_[startIndex + 1].position.z = std::cos(lat + kLatEvery) * std::sin(lon);
			resourcesUVSphere_->vertexData_[startIndex + 1].position.w = 1.0f;
			resourcesUVSphere_->vertexData_[startIndex + 1].texcoord.x = float(lonIndex) / float(segment);
			resourcesUVSphere_->vertexData_[startIndex + 1].texcoord.y = 1.0f - (float(latIndex + 1) / float(ring));
			resourcesUVSphere_->vertexData_[startIndex + 1].normal.x = resourcesUVSphere_->vertexData_[startIndex + 1].position.x;
			resourcesUVSphere_->vertexData_[startIndex + 1].normal.y = resourcesUVSphere_->vertexData_[startIndex + 1].position.y;
			resourcesUVSphere_->vertexData_[startIndex + 1].normal.z = resourcesUVSphere_->vertexData_[startIndex + 1].position.z;

			resourcesUVSphere_->vertexData_[startIndex + 2].position.x = std::cos(lat) * std::cos(lon + kLonEvery);
			resourcesUVSphere_->vertexData_[startIndex + 2].position.y = std::sin(lat);
			resourcesUVSphere_->vertexData_[startIndex + 2].position.z = std::cos(lat) * std::sin(lon + kLonEvery);
			resourcesUVSphere_->vertexData_[startIndex + 2].position.w = 1.0f;
			resourcesUVSphere_->vertexData_[startIndex + 2].texcoord.x = float(lonIndex + 1) / float(segment);
			resourcesUVSphere_->vertexData_[startIndex + 2].texcoord.y = 1.0f - (float(latIndex) / float(ring));
			resourcesUVSphere_->vertexData_[startIndex + 2].normal.x = resourcesUVSphere_->vertexData_[startIndex + 2].position.x;
			resourcesUVSphere_->vertexData_[startIndex + 2].normal.y = resourcesUVSphere_->vertexData_[startIndex + 2].position.y;
			resourcesUVSphere_->vertexData_[startIndex + 2].normal.z = resourcesUVSphere_->vertexData_[startIndex + 2].position.z;

			resourcesUVSphere_->vertexData_[startIndex + 3].position.x = std::cos(lat + kLatEvery) * std::cos(lon + kLonEvery);
			resourcesUVSphere_->vertexData_[startIndex + 3].position.y = std::sin(lat + kLatEvery);
			resourcesUVSphere_->vertexData_[startIndex + 3].position.z = std::cos(lat + kLatEvery) * std::sin(lon + kLonEvery);
			resourcesUVSphere_->vertexData_[startIndex + 3].position.w = 1.0f;
			resourcesUVSphere_->vertexData_[startIndex + 3].texcoord.x = float(lonIndex + 1) / float(segment);
			resourcesUVSphere_->vertexData_[startIndex + 3].texcoord.y = 1.0f - (float(latIndex + 1) / float(ring));
			resourcesUVSphere_->vertexData_[startIndex + 3].normal.x = resourcesUVSphere_->vertexData_[startIndex + 3].position.x;
			resourcesUVSphere_->vertexData_[startIndex + 3].normal.y = resourcesUVSphere_->vertexData_[startIndex + 3].position.y;
			resourcesUVSphere_->vertexData_[startIndex + 3].normal.z = resourcesUVSphere_->vertexData_[startIndex + 3].position.z;
		}
	}


	/*--------------
	    マテリアル
	--------------*/

	// 色やライティング
	resourcesUVSphere_->materialData_->color_ = color;
	resourcesUVSphere_->materialData_->enableLighting_ = static_cast<int32_t>(enableLighting);
	resourcesUVSphere_->materialData_->enableHalfLambert_ = static_cast<int32_t>(enableHalfLanbert);

	// UV座標変換用行列
	resourcesUVSphere_->materialData_->uvTransform_ = uvTransform->affineMatrix_;


	/*------------------
	    座標変換の行列
	------------------*/

	// 座標変換行列を取得する
	resourcesUVSphere_->transformationData_->world = worldTransform->worldMatrix_;
	resourcesUVSphere_->transformationData_->worldViewProjection = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*----------------------------
	    コマンドリストに設定する
	----------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// リソースの設定
	resourcesUVSphere_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(indexNum, 1, 0, 0, 0);
}


/// <summary>
/// 立方体を描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
void DirectXDraw::DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
	const Vector4& color, bool enableLighting, bool enableHalfLanbert)
{
	/*---------------
	    マテリアル
	---------------*/

	// UV座標変換用行列
	resourcesCube_->materialData_->uvTransform_ = uvTransform->affineMatrix_;
	
	// 色やライティング
	resourcesCube_->materialData_->color_ = color;
	resourcesCube_->materialData_->enableLighting_ = static_cast<int32_t>(enableLighting);
	resourcesCube_->materialData_->enableHalfLambert_ = static_cast<int32_t>(enableHalfLanbert);


	/*-------------
	    座標変換
	-------------*/

	// 座標変換用の行列を取得する
	resourcesCube_->transformationData_->world = worldTransform->worldMatrix_;
	resourcesCube_->transformationData_->worldViewProjection = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*---------------------------------
	    コマンドリストに設定を登録する
	---------------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// リソースの設定
	resourcesCube_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(36, 1, 0, 0, 0);
}


/// <summary>
/// スプライトを描画する
/// </summary>
/// <param name="textureHandle"></param>
void DirectXDraw::DrawSprite(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,
	const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color)
{
	/*------------------------
	    頂点データを入力する
	------------------------*/

	// 左下
	resourceSprite_->vertexData_[0].position = Vector4(p2.x, p2.y, p2.z, 1.0f);
	resourceSprite_->vertexData_[0].texcoord = Vector2(0.0f, 1.0f);

	// 左上
	resourceSprite_->vertexData_[1].position = Vector4(p0.x, p0.y, p0.z, 1.0f);
	resourceSprite_->vertexData_[1].texcoord = Vector2(0.0f, 0.0f);

	// 右下
	resourceSprite_->vertexData_[2].position = Vector4(p3.x, p3.y, p3.z, 1.0f);
	resourceSprite_->vertexData_[2].texcoord = Vector2(1.0f, 1.0f);

	// 右上
	resourceSprite_->vertexData_[3].position = Vector4(p1.x, p1.y, p1.z, 1.0f);
	resourceSprite_->vertexData_[3].texcoord = Vector2(1.0f, 0.0f);


	/*-------------------
	    マテリアル設定
	-------------------*/

	// 色
	resourceSprite_->materialData_->color_ = color;

	// UVトランスフォーム
	resourceSprite_->materialData_->uvTransform_ = uvTransform->affineMatrix_;


	/*------------------
		座標変換を行う
	------------------*/

	// 座標変換行列を入力する
	resourceSprite_->transformationData_->worldViewProjection = camera->viewMatrix_ * camera->projectionMatrix_;


	/*---------------------------
		コマンドリストに登録する
	---------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// リソースの設定
	resourceSprite_->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

#pragma endregion

#pragma region パーティクル描画処理

/// <summary>
/// 立方体パーティクルを描画する
/// </summary>
/// <param name="particles_"></param>
/// <param name="camera3d"></param>
void DirectXDraw::DrawParticleCube(const std::list<std::unique_ptr<Particle>>& particles, const ResourcesParticleCube* resourcesParticleCube,
	const Camera3D* camera3d, uint32_t textureHandle)
{
	/*----------------------------
	    座標変換データを入力する
	----------------------------*/

	int32_t index = 0;
	for (const std::unique_ptr<Particle>& particle : particles)
	{
		Matrix4x4 worldMatrix = MakeAffineMatrix(particle->GetScale(), particle->GetRotation(), particle->GetTranslation());

		resourcesCube_->transformationData_[index].world = worldMatrix;
		resourcesCube_->transformationData_[index].worldViewProjection = worldMatrix * camera3d->viewMatrix_ * camera3d->projectionMatrix_;

		index++;
	}


	/*---------------------------
		コマンドリストに登録する
	---------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	particlePSO_->SetPSOState();

	// リソースの設定
	resourcesParticleCube->SetCommandList();

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(36, static_cast<UINT>(particles.size()), 0, 0, 0);
}

#pragma endregion