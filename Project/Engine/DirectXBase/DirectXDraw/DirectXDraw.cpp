#include "DirectXDraw.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

/// <summary>
/// デストラクタ
/// </summary>
DirectXDraw::~DirectXDraw()
{
	// ModelStoreを終了する
	modelStore_->Finalize();

	// TextureStoreを終了する
	textureStore_->Finalize();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="commandList"></param>
/// <param name="device"></param>
void DirectXDraw::Initialize(LogFile* logFile, DirectXHeap* directXHeap, DirectXBuffering* directXBuffering, const int32_t* kClientWidth, const int32_t* kClientHeight,
	ID3D12GraphicsCommandList* commandList, ID3D12Device* device)
{
	// nullptrチェック
	assert(logFile);
	assert(directXHeap);
	assert(directXBuffering);
	assert(kClientWidth);
	assert(kClientHeight);
	assert(commandList);
	assert(device);

	// 引数を受け取る
	logFile_ = logFile;
	directXHeap_ = directXHeap;
	directXBuffering_ = directXBuffering;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	commandList_ = commandList;
	device_ = device;


	// DirectXシェーダコンパイラの生成と初期化
	directXShaderCompiler_ = std::make_unique<DirectXShaderCompile>();
	directXShaderCompiler_->Initialize(logFile_);

	// テクスチャ格納場所の生成と初期化
	textureStore_ = TextureStore::GetInstance();
	textureStore_->Initialize(directXHeap_, logFile_, device_, commandList_);


	// モデル格納場所の生成と初期化
	modelStore_ = ModelStore::GetInstance();
	modelStore_->Initialize(textureStore_, device_, commandList_, directXHeap_);


	// オフスクリーン描画の生成と初期化
	offscreenDraw_ = std::make_unique<OffscreenDraw>();
	offscreenDraw_->Initialize(device_, commandList_, logFile_, directXBuffering_, directXHeap_, directXShaderCompiler_.get());


	// プリミティブ用PSOの生成と初期化
	primitivePSO_ = std::make_unique<OrganizePSOPrimitive>();
	primitivePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);

	// スプライト用PSOの生成と初期化
	spritePSO_ = std::make_unique<OrganizePSOSprite>();
	spritePSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);

	// スキニングモデル用PSOの生成と初期化
	skinningModelPSO_ = std::make_unique<OrganizePSOSkinningModel>();
	skinningModelPSO_->Initialize(logFile_, directXShaderCompiler_.get(), commandList_, device_);


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
	resourcesUVSphere_ = std::make_unique<PrimitiveResourcesUVSphere>();
	resourcesUVSphere_->Initialize(device_, commandList_);

	// 立方体用リソースの生成と初期化
	resourcesCube_ = std::make_unique<PrimitiveResourcesCube>();
	resourcesCube_->Initialize(device_, commandList_);

	// スプライト用リソースの生成と初期化
	resourceSprite_ = std::make_unique<PrimitiveResourcesSprite>();
	resourceSprite_->Initialize(device_, commandList_);


	// プリミティブ用のCBVリソースを生成する
	for (uint32_t i = 0; i < kDrawPrimitiveNum; ++i)
	{
		// マテリアルリソース
		std::unique_ptr<MaterialResourcesDataCBV> materialResource = std::make_unique<MaterialResourcesDataCBV>();
		materialResource->Initialize(device_, commandList_);
		primitiveMaterialResources_.push_back(std::move(materialResource));

		// 座標変換リソース
		std::unique_ptr<TransformationResourcesDataCBV> transformationResource = std::make_unique<TransformationResourcesDataCBV>();
		transformationResource->Initialize(device_, commandList_);
		primitiveTransformationResources_.push_back(std::move(transformationResource));
	}


	// 平行光源リソースの生成と初期化
	resourcesDirectionalLight_ = std::make_unique<DirectionalLightResourcesData>();
	resourcesDirectionalLight_->Initialize(directXHeap_, device_, commandList_, 512);

	resourcesDirectionalLight_->lightData_[0].direction = Vector3(0.0f, -1.0f, 0.0f);
	resourcesDirectionalLight_->lightData_[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	resourcesDirectionalLight_->lightData_[0].intensity = 1.0f;

	*resourcesDirectionalLight_->numLightData_ = 1;


	// ポイントライトリソースの生成と初期化
	resourcesPointLight_ = std::make_unique<PointLightResourcesData>();
	resourcesPointLight_->Initialize(directXHeap_, device_, commandList_, 512);


	// スポットライトリソースの生成と初期化
	resourcesSpotLight_ = std::make_unique<SpotLightResourcesData>();
	resourcesSpotLight_->Initialize(directXHeap_, device_, commandList_, 512);


	// メインカメラリソースの生成と初期化
	resourcesMainCamera_ = std::make_unique<MainCameraResourcesDataCBV>();
	resourcesMainCamera_->Initialize(device_, commandList_);
}

/// <summary>
/// ブレンドモードをリセットする
/// </summary>
void DirectXDraw::ResetBlendMode()
{
	primitivePSO_->ResetBlendMode();
	spritePSO_->ResetBlendMode();
}

/// <summary>
/// オフスクリーンをクリアする
/// </summary>
void DirectXDraw::OffscreenClear(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
	offscreenDraw_->ClearOffscree(dsvHandle);
}



/// <summary>
/// モデルを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="uvTransform"></param>
/// <param name="camera"></param>
/// <param name="modelHandle"></param>
/// <param name="material"></param>
void DirectXDraw::DrawModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t modelHandle,
	const Material* material)
{
	// モデル情報を取得する
	BaseModelResources* modelResource = modelStore_->GetModelInfo(modelHandle);

	// モデルデータを取得する
	ModelData modelData = modelResource->GetModelData();


	// 拡張子名で描画方法を変える
	
	// objファイル
	if (modelResource->GetExtName().find(".obj") == 0)
	{
		DrawObjModel(worldTransform, uvTransform, camera, modelResource, material);
	}

	// gltfファイル
	if (modelResource->GetExtName().find(".gltf") == 0)
	{
		// スキニングのアニメーションを行う
		if (modelData.isSkinning && modelData.isAnimation)
		{
			DrawGltfSkinningModel(worldTransform, uvTransform, camera, modelResource, material);
		}
		else if(modelData.isAnimation)
		{
			// アニメーションのみを行う
			DrawGltfAnimationModel(worldTransform, uvTransform, camera, modelResource, material);
		}
		else
		{
			// そのまま描画する
			DrawGltfModel(worldTransform, uvTransform, camera, modelResource, material);
		}
	}
}

/// <summary>
/// モデルを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="uvTransform"></param>
/// <param name="camera"></param>
/// <param name="modelHandle"></param>
/// <param name="color"></param>
/// <param name="enableLighting"></param>
/// <param name="enableHalfLanbert"></param>
void DirectXDraw::DrawGltfModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
	const Material* material)
{
	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();


	// wvp行列
	Matrix4x4 worldViewProjectionMatrix = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;

	Node rootNode = modelResource->GetRootNode();
	std::vector<Matrix4x4> nodeWorldMatrix;
	GetNodeWorldMatrix(nodeWorldMatrix, rootNode);
	

	// メッシュの数を描画する
	for (uint32_t meshIndex = 0; meshIndex < modelResource->GetNumMesh(); ++meshIndex)
	{
		/*-----------------------------
			マテリアルデータを入力する
		-----------------------------*/
	
		// UV座標
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

		// マテリアル
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;

		// 拡散反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

		// 鏡面反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


		/*----------------------------
		    座標変換データを入力する
		----------------------------*/

		primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
			MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection =
			nodeWorldMatrix[meshIndex] * worldViewProjectionMatrix;


		// ビューポート、シザー矩形の設定
		commandList_->RSSetViewports(1, &viewport_);
		commandList_->RSSetScissorRects(1, &scissorRect_);

		// PSOの設定
		primitivePSO_->SetPSOState();

		// モデルの頂点、インデックスの設定
		modelResource->Register(meshIndex);

		// モデルリソースの設定
		primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

		// 座標変換リソースの設定
		primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

		// メインカメラリソースの設定
		resourcesMainCamera_->Register(5);

		// 平行光源リソースの設定
		resourcesDirectionalLight_->Register(3, 4);

		// ポイントライトリソースの設定
		resourcesPointLight_->Register(6, 7);

		// スポットライトリソースの設定
		resourcesSpotLight_->Register(8, 9);

		// テクスチャのSRVを設定する
		commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(modelResource->GetTextureHandle(meshIndex)));

		// 形状の設定
		commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ドローコール
		commandList_->DrawIndexedInstanced(modelResource->GetNumIndex(meshIndex), 1, 0, 0, 0);

		
		// 描画したプリミティブをカウントする
		CountDrawPrimitive();
	}
}

/// <summary>
/// Gltfファイルのアニメーション付きのモデルを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="uvTransform"></param>
/// <param name="camera"></param>
/// <param name="modelResource"></param>
/// <param name="material"></param>
void DirectXDraw::DrawGltfAnimationModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
	const Material* material)
{
	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();

	// wvp行列
	Matrix4x4 worldViewProjectionMatrix = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;

	Node rootNode = modelResource->GetRootNode();
	std::vector<Matrix4x4> nodeWorldMatrix;
	GetNodeWorldMatrix(nodeWorldMatrix, rootNode);


	// メッシュの数を描画する
	for (uint32_t meshIndex = 0; meshIndex < modelResource->GetNumMesh(); ++meshIndex)
	{
		/*-----------------------------
			マテリアルデータを入力する
		-----------------------------*/

		// UV座標
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

		// マテリアル
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;

		// 拡散反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

		// 鏡面反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


		/*----------------------------
			座標変換データを入力する
		----------------------------*/

		primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
			MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection =
			nodeWorldMatrix[meshIndex] * worldViewProjectionMatrix;


		// ビューポート、シザー矩形の設定
		commandList_->RSSetViewports(1, &viewport_);
		commandList_->RSSetScissorRects(1, &scissorRect_);

		// PSOの設定
		primitivePSO_->SetPSOState();

		// モデルの頂点、インデックスの設定
		modelResource->Register(meshIndex);

		// モデルリソースの設定
		primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

		// 座標変換リソースの設定
		primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

		// メインカメラリソースの設定
		resourcesMainCamera_->Register(5);

		// 平行光源リソースの設定
		resourcesDirectionalLight_->Register(3, 4);

		// ポイントライトリソースの設定
		resourcesPointLight_->Register(6, 7);

		// スポットライトリソースの設定
		resourcesSpotLight_->Register(8, 9);

		// テクスチャのSRVを設定する
		commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(modelResource->GetTextureHandle(meshIndex)));

		// 形状の設定
		commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ドローコール
		commandList_->DrawIndexedInstanced(modelResource->GetNumIndex(meshIndex), 1, 0, 0, 0);


		// 描画したプリミティブをカウントする
		CountDrawPrimitive();
	}
}

/// <summary>
/// Gltfファイルのスキニングを行うモデルを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="uvTransform"></param>
/// <param name="camera"></param>
/// <param name="modelResource"></param>
/// <param name="material"></param>
void DirectXDraw::DrawGltfSkinningModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
	const Material* material)
{
	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();


	// wvp行列
	Matrix4x4 worldViewProjectionMatrix = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;

	Node rootNode = modelResource->GetRootNode();
	std::vector<Matrix4x4> nodeWorldMatrix;
	GetNodeWorldMatrix(nodeWorldMatrix, rootNode);


	// メッシュの数を描画する
	for (uint32_t meshIndex = 0; meshIndex < modelResource->GetNumMesh(); ++meshIndex)
	{
		/*-----------------------------
			マテリアルデータを入力する
		-----------------------------*/

		// UV座標
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

		// マテリアル
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;

		// 拡散反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

		// 鏡面反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


		/*----------------------------
			座標変換データを入力する
		----------------------------*/

		primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
			MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection =
			nodeWorldMatrix[meshIndex] * worldViewProjectionMatrix;


		// ビューポート、シザー矩形の設定
		commandList_->RSSetViewports(1, &viewport_);
		commandList_->RSSetScissorRects(1, &scissorRect_);

		// PSOの設定
		primitivePSO_->SetPSOState();

		// モデルの頂点、インデックスの設定
		modelResource->Register(meshIndex);

		// モデルリソースの設定
		primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

		// 座標変換リソースの設定
		primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

		// メインカメラリソースの設定
		resourcesMainCamera_->Register(5);

		// 平行光源リソースの設定
		resourcesDirectionalLight_->Register(3, 4);

		// ポイントライトリソースの設定
		resourcesPointLight_->Register(6, 7);

		// スポットライトリソースの設定
		resourcesSpotLight_->Register(8, 9);

		// テクスチャのSRVを設定する
		commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(modelResource->GetTextureHandle(meshIndex)));

		// 形状の設定
		commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ドローコール
		commandList_->DrawIndexedInstanced(modelResource->GetNumIndex(meshIndex), 1, 0, 0, 0);


		// 描画したプリミティブをカウントする
		CountDrawPrimitive();
	}
}

/// <summary>
/// Objファイルのモデルを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="uvTransform"></param>
/// <param name="camera"></param>
/// <param name="modelHandle"></param>
/// <param name="material"></param>
void DirectXDraw::DrawObjModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
	const Material* material)
{
	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();


	// wvp行列
	Matrix4x4 worldViewProjectionMatrix = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	// メッシュの数を描画する
	for (uint32_t meshIndex = 0; meshIndex < modelResource->GetNumMesh(); ++meshIndex)
	{
		/*-----------------------------
			マテリアルデータを入力する
		-----------------------------*/

		// UV座標
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

		// マテリアル
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;

		// 拡散反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

		// 鏡面反射
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
		primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


		/*----------------------------
			座標変換データを入力する
		----------------------------*/

		primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
			MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));
		primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection = worldViewProjectionMatrix;


		// ビューポート、シザー矩形の設定
		commandList_->RSSetViewports(1, &viewport_);
		commandList_->RSSetScissorRects(1, &scissorRect_);

		// PSOの設定
		primitivePSO_->SetPSOState();

		// モデルの頂点、インデックスの設定
		modelResource->Register(meshIndex);

		// モデルリソースの設定
		primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

		// 座標変換リソースの設定
		primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

		// メインカメラリソースの設定
		resourcesMainCamera_->Register(5);

		// 平行光源リソースの設定
		resourcesDirectionalLight_->Register(3, 4);

		// ポイントライトリソースの設定
		resourcesPointLight_->Register(6, 7);

		// スポットライトリソースの設定
		resourcesSpotLight_->Register(8, 9);

		// テクスチャのSRVを設定する
		commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(modelResource->GetTextureHandle(meshIndex)));

		// 形状の設定
		commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ドローコール
		commandList_->DrawIndexedInstanced(modelResource->GetNumIndex(meshIndex), 1, 0, 0, 0);


		// 描画したプリミティブをカウントする
		CountDrawPrimitive();
	}
}

/// <summary>
/// UV球を描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
/// <param name="segment"></param>
/// <param name="ring"></param>
void DirectXDraw::DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
	const Material* material ,int32_t segment, int32_t ring)
{
	// セグメントとリングの数を制限する
	segment = std::max(segment, resourcesUVSphere_->GetMinSegment());
	segment = std::min(segment, resourcesUVSphere_->GetMaxSegment());
	ring = std::max(ring, resourcesUVSphere_->GetMinRing());
	ring = std::min(ring, resourcesUVSphere_->GetMaxRing());

	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();

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


	/*-----------------------------
	    マテリアルデータを入力する
	-----------------------------*/

	// UV座標
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

	// 色
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;
	
	// 拡散反射
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

	// 鏡面反射
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


	/*------------------
	    座標変換の行列
	------------------*/

	// 座標変換行列を取得する
	primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;

	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
		MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));

	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection =
		worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*----------------------------
	    コマンドリストに設定する
	----------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// UV球の設定
	resourcesUVSphere_->Register();

	// マテリアルリソースの設定
	primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

	// 座標変換リソースの設定
	primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

	// メインカメラリソースの設定
	resourcesMainCamera_->Register(5);

	// 平行光源リソースの設定
	resourcesDirectionalLight_->Register(3, 4);

	// ポイントライトリソースの設定
	resourcesPointLight_->Register(6, 7);

	// スポットライトリソースの設定
	resourcesSpotLight_->Register(8, 9);

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(indexNum, 1, 0, 0, 0);


	// 描画したプリミティブをカウントする
	CountDrawPrimitive();
}


/// <summary>
/// 立方体を描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
void DirectXDraw::DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
	const Material* material)
{
	// カメラの値を取得する
	resourcesMainCamera_->data_->worldPosition = camera->GetWorldPosition();

	/*------------------------------
	    マテリアルデータを入力する
	------------------------------*/

	// UV座標
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

	// 色
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = material->color_;
	
	// 拡散反射
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(material->enableLighting_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(material->enableHalfLambert_);

	// 鏡面反射
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(material->enableSpecular_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(material->enableBlinnPhong_);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = material->shininess_;


	/*-------------
	    座標変換
	-------------*/

	// 座標変換用の行列を取得する
	primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = worldTransform->worldMatrix_;

	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose =
		MakeInverseMatrix4x4(MakeTransposeMatrix4x4(worldTransform->worldMatrix_));

	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection =
		worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;


	/*---------------------------------
	    コマンドリストに設定を登録する
	---------------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	primitivePSO_->SetPSOState();

	// 立方体の設定
	resourcesCube_->Register();

	// マテリアルリソースの設定
	primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

	// 座標変換リソースの設定
	primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

	// メインカメラリソースの設定
	resourcesMainCamera_->Register(5);

	// 平行光源リソースの設定
	resourcesDirectionalLight_->Register(3, 4);

	// ポイントライトリソースの設定
	resourcesPointLight_->Register(6, 7);

	// スポットライトリソースの設定
	resourcesSpotLight_->Register(8, 9);

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(36, 1, 0, 0, 0);


	// 描画したプリミティブをカウントする
	CountDrawPrimitive();
}


/// <summary>
/// スプライトを描画する
/// </summary>
/// <param name="textureHandle"></param>
void DirectXDraw::DrawSprite(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,const Vector2& textureLeftTop, const Vector2& textureSize,
	const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color)
{
	/*------------------------
	    頂点データを入力する
	------------------------*/

	// テクスチャの幅
	float textureWidth = textureStore_->GetTextureWidth(textureHandle);
	float textureHeight = textureStore_->GetTextureHeight(textureHandle);

	float tex_left = textureLeftTop.x / textureWidth;
	float tex_right = (textureLeftTop.x + textureSize.x) / textureWidth;
	float tex_top = textureLeftTop.y / textureHeight;
	float tex_bottom = (textureLeftTop.y + textureSize.y) / textureHeight;
	

	// 左下
	resourceSprite_->vertexData_[0].position = Vector4(p2.x, p2.y, p2.z, 1.0f);
	resourceSprite_->vertexData_[0].texcoord = Vector2(tex_left, tex_bottom);

	// 左上
	resourceSprite_->vertexData_[1].position = Vector4(p0.x, p0.y, p0.z, 1.0f);
	resourceSprite_->vertexData_[1].texcoord = Vector2(tex_left, tex_top);

	// 右下
	resourceSprite_->vertexData_[2].position = Vector4(p3.x, p3.y, p3.z, 1.0f);
	resourceSprite_->vertexData_[2].texcoord = Vector2(tex_right, tex_bottom);

	// 右上
	resourceSprite_->vertexData_[3].position = Vector4(p1.x, p1.y, p1.z, 1.0f);
	resourceSprite_->vertexData_[3].texcoord = Vector2(tex_right, tex_top);


	/*-------------------
	    マテリアル設定
	-------------------*/

	// UV座標
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->uvTransform_ = uvTransform->affineMatrix_;

	// 色
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->color_ = color;

	// ライティングは行わない
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableLighting_ = static_cast<int32_t>(false);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableHalfLambert_ = static_cast<int32_t>(false);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableSpecular_ = static_cast<int32_t>(false);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->enableBlinnPhong_ = static_cast<int32_t>(false);
	primitiveMaterialResources_[drawPrimitiveCount_]->data_->shininess_ = 1.0f;


	/*------------------
		座標変換を行う
	------------------*/

	// 座標変換行列を入力する
	primitiveTransformationResources_[drawPrimitiveCount_]->data_->world = MakeIdentityMatrix4x4();
	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldInverseTranspose = MakeIdentityMatrix4x4();
	primitiveTransformationResources_[drawPrimitiveCount_]->data_->worldViewProjection = camera->viewMatrix_ * camera->projectionMatrix_;


	/*---------------------------
		コマンドリストに登録する
	---------------------------*/

	// ビューポート、シザー矩形の設定
	commandList_->RSSetViewports(1, &viewport_);
	commandList_->RSSetScissorRects(1, &scissorRect_);

	// PSOの設定
	spritePSO_->SetPSOState();

	// スプライトの設定
	resourceSprite_->Register();

	// マテリアルリソースの設定
	primitiveMaterialResources_[drawPrimitiveCount_]->Register(0);

	// 座標変換リソースの設定
	primitiveTransformationResources_[drawPrimitiveCount_]->Register(1);

	// テクスチャのSRVを設定する
	commandList_->SetGraphicsRootDescriptorTable(2, textureStore_->GetGPUDescriptorHandle(textureHandle));

	// 形状の設定
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ドローコール
	commandList_->DrawIndexedInstanced(6, 1, 0, 0, 0);


	// 描画したプリミティブをカウントする
	CountDrawPrimitive();
}