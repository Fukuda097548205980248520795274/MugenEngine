#pragma once
#define NOMINMAX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>
#include <numbers>

#include "DirectXShaderCompile/DirectXShaderCompile.h"
#include "../DirectXHeap/DirectXHeap.h"
#include "TextureStore/TextureStore.h"
#include "ModelStore/ModelStore.h"

#include "BaseMesh/MeshUVSphere/MeshUVSphere.h"
#include "BaseMesh/MeshCube/MeshCube.h"
#include "BaseMesh/MeshSprite/MeshSprite.h"
#include "BaseMesh/MeshModel/MeshModel.h"

#include "BaseOrganizePSO/OrganizePSOPrimitive/OrganizePSOPrimitive.h"

#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesCube/PrimitiveResourcesCube.h"
#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesSprite/PrimitiveResourcesSprite.h"
#include "ResourcesData/PrimitiveResourcesData/PrimitiveResourcesUVSphere/PrimitiveResourcesUVSphere.h"

#include "ResourcesData/DirectionalLightResourcesData/DirectionalLightResourcesData.h"

#include "ResourcesData/MainCameraResourcesDataCBV/MainCameraResourcesDataCBV.h"

class DirectXDraw
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="commandList"></param>
	/// <param name="device"></param>
	void Initialize(LogFile* logFile,DirectXHeap* directXHeap, const int32_t* kClientWidth, const int32_t* kClientHeight,
		ID3D12GraphicsCommandList* commandList, ID3D12Device* device);

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
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode) { primitivePSO_->SetBlendMode(blendMode); }

	/// <summary>
	/// ブレンドモードをリセットする
	/// </summary>
	void ResetBlendMode();


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
	void DrawModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t modelHandle,
		const Vector4& color, bool enableLighting, bool enableHalfLanbert, bool enableSpecular, float shininess);

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert, bool enableSpecular, float shininess, int32_t segment, int32_t ring);

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert, bool enableSpecular, float shininess);

	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="p0"></param>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <param name="p3"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawSprite(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,
		const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color);


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

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
	std::unique_ptr<TextureStore> textureStore_ = nullptr;

	// モデル格納場所
	std::unique_ptr<ModelStore> modelStore_ = nullptr;


	// プリミティブ用PSO
	std::unique_ptr<OrganizePSOPrimitive> primitivePSO_ = nullptr;


	// ビューポート
	D3D12_VIEWPORT viewport_{};

	// シザー
	D3D12_RECT scissorRect_{};




	// UV球用のリソース
	std::unique_ptr<PrimitiveResourcesUVSphere> resourcesUVSphere_ = nullptr;

	// 立方体用のリソース
	std::unique_ptr<PrimitiveResourcesCube> resourcesCube_ = nullptr;

	// スプライト用のリソース
	std::unique_ptr<PrimitiveResourcesSprite> resourceSprite_ = nullptr;


	// 平行光源リソース
	std::unique_ptr<DirectionalLightResourcesData> resourcesDirectionalLight_ = nullptr;

	// メインカメラリソース
	std::unique_ptr<MainCameraResourcesDataCBV> resourcesMainCamera_ = nullptr;
};

