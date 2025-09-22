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

#include "BaseMesh/MeshUVSphere/MeshUVSphere.h"
#include "BaseMesh/MeshCube/MeshCube.h"

#include "BaseMesh/WorldTransform2D/WorldTransform2D.h"

#include "Camera/Camera2D/Camera2D.h"
#include "Camera/Camera3D/Camera3D.h"

#include "BaseOrganizePSO/OrganizePSOPrimitive/OrganizePSOPrimitive.h"
#include "BaseOrganizePSO/OrganizePSOSprite/OrganizePSOSprite.h"

#include "ResourcesData/ResourcesUVSphere/ResourcesUVSphere.h"
#include "ResourcesData/ResourcesCube/ResourcesCube.h"
#include "ResourcesData/ResourcesSprite/ResourcesSprite.h"

#include "../../Func/LoadTexture/LoadTexture.h"

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
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode) { primitivePSO_->SetBlendMode(blendMode); }

	/// <summary>
	/// ブレンドモードをリセットする
	/// </summary>
	void ResetBlendMode();


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
	void DrawUVSphere(const WorldTransform3D* worldTransform,const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle, 
		const Vector4& color,bool enableLighting, bool enableHalfLanbert, int32_t segment, int32_t ring);

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert);

	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="textureHandle"></param>
	void DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle);


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


	// プリミティブ用PSO
	std::unique_ptr<OrganizePSOPrimitive> primitivePSO_ = nullptr;

	// スプライト用PSO
	std::unique_ptr<OrganizePSOSprite> spritePSO_ = nullptr;


	// ビューポート
	D3D12_VIEWPORT viewport_{};

	// シザー
	D3D12_RECT scissorRect_{};




	// UV球用のリソース
	std::unique_ptr<ResourcesUVSphere> resourcesUVSphere_ = nullptr;

	// 立方体用のリソース
	std::unique_ptr<ResourcesCube> resourcesCube_ = nullptr;

	// スプライト用のリソース
	std::unique_ptr<ResourcesSprite> resourceSprite_ = nullptr;
};

