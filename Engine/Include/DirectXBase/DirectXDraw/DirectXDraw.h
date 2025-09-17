#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "DirectXShaderCompile/DirectXShaderCompile.h"
#include "../DirectXHeap/DirectXHeap.h"
#include "TextureStore/TextureStore.h"

#include "WorldTransform/WorldTransform.h"
#include "Camera/Camera.h"

#include "BaseOrganizePSO/OrganizePSOPrimitive/OrganizePSOPrimitive.h"
#include "BaseOrganizePSO/OrganizePSOSprite/OrganizePSOSprite.h"

#include "ResourcesTriangle/ResourcesTriangle.h"
#include "ResourcesSprite/ResourcesSprite.h"

#include "Transform/Transform.h"

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
	/// 三角形を描画する
	/// </summary>
	void DrawTriangle(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle);

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


	// 三角形用のリソース
	std::unique_ptr<ResourcesTriangle> resourcesTriangle_ = nullptr;

	// スプライト用のリソース
	std::unique_ptr<ResourcesSprite> resourceSprite_ = nullptr;
};

