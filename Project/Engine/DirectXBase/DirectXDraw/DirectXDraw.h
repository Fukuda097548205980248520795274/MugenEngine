#pragma once
#define NOMINMAX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>
#include <numbers>

#include "DirectXShaderCompile/DirectXShaderCompile.h"
#include "../DirectXHeap/DirectXHeap.h"
#include "DirectXBase/DirectXBuffering/DirectXBuffering.h"
#include "TextureStore/TextureStore.h"
#include "ModelStore/ModelStore.h"
#include "OffscreenDraw/OffscreenDraw.h"

#include "BaseMesh/MeshUVSphere/MeshUVSphere.h"
#include "BaseMesh/MeshPlane/MeshPlane.h"
#include "BaseMesh/MeshCube/MeshCube.h"
#include "BaseMesh/MeshSprite/MeshSprite.h"
#include "BaseMesh/MeshModel/MeshModel.h"

#include "BaseOrganizePSO/OrganizePSOPrimitive/OrganizePSOPrimitive.h"
#include "BaseOrganizePSO/OrganizePSOSprite/OrganizePSOSprite.h"
#include "BaseOrganizePSO/OrganizePSOSkinningModel/OrganizePSOSkinningModel.h"

#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesPlane/PrimitiveResourcesPlane.h"
#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesCube/PrimitiveResourcesCube.h"
#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesSprite/PrimitiveResourcesSprite.h"
#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesUVSphere/PrimitiveResourcesUVSphere.h"

#include "ResourcesData/DirectionalLightResourcesData/DirectionalLightResourcesData.h"
#include "ResourcesData/PointLightResourcesData/PointLightResourcesData.h"
#include "ResourcesData/SpotLightResourcesData/SpotLightResourcesData.h"

#include "ResourcesData/TransformationResourcesDataCBV/TransformationResourcesDataCBV.h"
#include "ResourcesData/MaterialResourcesDataCBV/MaterialResourcesDataCBV.h"

#include "ResourcesData/MainCameraResourcesDataCBV/MainCameraResourcesDataCBV.h"

class DirectXDraw
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DirectXDraw();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="commandList"></param>
	/// <param name="device"></param>
	void Initialize(LogFile* logFile,DirectXHeap* directXHeap, DirectXBuffering* directXBuffering, const int32_t* kClientWidth, const int32_t* kClientHeight,
		ID3D12GraphicsCommandList* commandList, ID3D12Device* device);

	/// <summary>
	/// 描画したプリミティブのカウントを初期化する
	/// </summary>
	void InitializeDrawNum() { drawPrimitiveCount_ = 0; offscreenDraw_->ResetNumOffscreen(); }

	/// <summary>
	/// 描画したプリミティブをカウントする
	/// </summary>
	void CountDrawPrimitive() { drawPrimitiveCount_++; }

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath) { return textureStore_->LoadTexture(filePath); }

	/// <summary>
	/// モデルを読み込む
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	uint32_t LoadModel(const std::string& directory, const std::string& fileName) { return modelStore_->LoadModel(directory, fileName); }

	/// <summary>
	/// アニメーションフラグのGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	bool IsAnimation(uint32_t modelHandle)const { return modelStore_->IsAnimation(modelHandle); }

	/// <summary>
	/// アニメーション時間のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	float GetAnimationDuration(uint32_t modelHandle)const { return modelStore_->GetAnimationDuration(modelHandle); }

	/// <summary>
	/// テクスチャの横幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureWidth(uint32_t textureHandle)const { return textureStore_->GetTextureWidth(textureHandle); }

	/// <summary>
	/// テクスチャの縦幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureHeight(uint32_t textureHandle)const { return textureStore_->GetTextureHeight(textureHandle); }

	/// <summary>
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode) { primitivePSO_->SetBlendMode(blendMode); }

	/// <summary>
	/// ブレンドモードをリセットする
	/// </summary>
	void ResetBlendMode();


#pragma region オフスクリーン

	/// <summary>
	/// オフスクリーンをクリアする
	/// </summary>
	void OffscreenClear(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

	/// <summary>
	/// 最終的なオフスクリーンをスワップチェーンにコピーする
	/// </summary>
	void DrawRtvToSwapChain() { offscreenDraw_->DrawRtvToSwapChain(); };

	/// <summary>
	/// 最後に使用したオフスクリーンのGPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetLastOffscreenDescriptorHandleGPU()const { return offscreenDraw_->GetLastOffscreenDescriptorHandleGPU(); }

	/// <summary>
	/// 最後に使用したオフスクリーンのリソースを取得する
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetLastOffscreenResource()const { return offscreenDraw_->GetLastOffscreenResource(); }

#pragma endregion


#pragma region 描画処理

	/// <summary>
	/// モデルを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="modelHandle"></param>
	/// <param name="material"></param>
	void DrawModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t modelHandle,
		const Material* material, float animationTimer);

private:

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
	void DrawGltfModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
		const Material* material);

	/// <summary>
	/// Gltfファイルのアニメーション付きのモデルを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="modelResource"></param>
	/// <param name="material"></param>
	void DrawGltfAnimationModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
		const Material* material, float animationTimer);

	/// <summary>
	/// Gltfファイルのスキニングを行うモデルを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="modelResource"></param>
	/// <param name="material"></param>
	void DrawGltfSkinningModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
		const Material* material, float animationTimer);

	/// <summary>
	/// Objファイルのモデルを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="modelHandle"></param>
	/// <param name="material"></param>
	void DrawObjModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, BaseModelResources* modelResource,
		const Material* material);

public:

	/// <summary>
	/// 平面を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="material"></param>
	void DrawPlane(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
		const Material* material);

	/// <summary>
	/// UV球を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="color"></param>
	/// <param name="enableLighting"></param>
	/// <param name="enableHalfLanbert"></param>
	/// <param name="segment"></param>
	/// <param name="ring"></param>
	void DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
		const Material* material, int32_t segment, int32_t ring);

	/// <summary>
	/// 立方体を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="color"></param>
	/// <param name="enableLighting"></param>
	/// <param name="enableHalfLanbert"></param>
	void DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
		const Material* material);

	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="p0"></param>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="p3"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawSprite(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector2& textureLeftTop, const Vector2& size,
		const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color);

#pragma endregion

#pragma region ポストエフェクト

	

#pragma endregion


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// DirectXバッファリング
	DirectXBuffering* directXBuffering_ = nullptr;

	// クライアント領域の横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域の縦幅
	const int32_t* kClientHeight_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;




	// DirectXシェーダコンパイラ
	std::unique_ptr<DirectXShaderCompile> directXShaderCompiler_ = nullptr;

	// テクスチャ格納場所
	TextureStore* textureStore_ = nullptr;

	// モデル格納場所
	ModelStore* modelStore_ = nullptr;

	// オフスクリーン描画
	std::unique_ptr<OffscreenDraw> offscreenDraw_ = nullptr;


	// プリミティブ用PSO
	std::unique_ptr<OrganizePSOPrimitive> primitivePSO_ = nullptr;

	// スプライト用PSO
	std::unique_ptr<OrganizePSOSprite> spritePSO_ = nullptr;

	// スキニングモデル用PSO
	std::unique_ptr<OrganizePSOSkinningModel> skinningModelPSO_ = nullptr;


	// ビューポート
	D3D12_VIEWPORT viewport_{};

	// シザー
	D3D12_RECT scissorRect_{};



	// 平面用のリソース
	std::unique_ptr<PrimitiveResourcesPlane> resourcesPlane_ = nullptr;

	// UV球用のリソース
	std::unique_ptr<PrimitiveResourcesUVSphere> resourcesUVSphere_ = nullptr;

	// 立方体用のリソース
	std::unique_ptr<PrimitiveResourcesCube> resourcesCube_ = nullptr;

	// スプライト用のリソース
	std::unique_ptr<PrimitiveResourcesSprite> resourceSprite_ = nullptr;


	// 描画できるプリミティブの数
	const uint32_t kDrawPrimitiveNum = 1024;

	// 描画したプリミティブのカウント
	uint32_t drawPrimitiveCount_ = 0;


	// プリミティブ用のマテリアルリソース
	std::vector<std::unique_ptr<MaterialResourcesDataCBV>> primitiveMaterialResources_;

	// プリミティブ用の座標変換リソース
	std::vector<std::unique_ptr<TransformationResourcesDataCBV>> primitiveTransformationResources_;



	// 平行光源リソース
	std::unique_ptr<DirectionalLightResourcesData> resourcesDirectionalLight_ = nullptr;

	// ポイントライトリソース
	std::unique_ptr<PointLightResourcesData> resourcesPointLight_ = nullptr;

	// スポットライトリソース
	std::unique_ptr<SpotLightResourcesData> resourcesSpotLight_ = nullptr;


	// メインカメラリソース
	std::unique_ptr<MainCameraResourcesDataCBV> resourcesMainCamera_ = nullptr;
};

