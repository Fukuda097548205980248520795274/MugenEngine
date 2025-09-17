#pragma once
#include "DirectXDevice/DirectXDevice.h"
#include "DirectXCommand/DirectXCommand.h"
#include "DirectXHeap/DirectXHeap.h"
#include "DirectXBuffering/DirectXBuffering.h"
#include "DirectXDebug/DirectXDebug.h"
#include "../Func/DirectXTransitionBarrier/DirectXTransitionBarrier.h"
#include "DirectXFence/DirectXFence.h"
#include "DirectXDraw/DirectXDraw.h"
#include "ResourcesDepthStencil/ResourcesDepthStencil.h"

#include "../../../Externals/ImGui/imgui.h"
#include "../../../Externals/ImGui/imgui_impl_dx12.h"
#include "../../../Externals/ImGui/imgui_impl_win32.h"

class DirectXBase
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DirectXBase();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(LogFile* logFile, HWND hwnd, const int32_t* kClientWidth, const int32_t* kClientHeight);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath) { return directXDraw_->LoadTexture(filePath); }

	// スプライトを描画する
	void DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle)
	{directXDraw_->DrawSprite(worldTransform, camera, textureHandle);}

	/// <summary>
	/// UV球を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="segment"></param>
	/// <param name="ring"></param>
	void DrawUVSphere(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle,
		int32_t segment, int32_t ring)
	{directXDraw_->DrawUVSphere(worldTransform, camera, textureHandle, segment, ring);}

	/// <summary>
	/// 立方体を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawCube(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle)
	{directXDraw_->DrawCube(worldTransform, camera, textureHandle);}

	
private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// ウィンドウハンドル
	HWND hwnd_{};

	// 画面の横幅
	const int32_t* kClientWidth_ = nullptr;

	// 画面の縦幅
	const int32_t* kClientHeight_ = nullptr;



	// DirectXデバイス
	std::unique_ptr<DirectXDevice> directXDevice_ = nullptr;
	
	// DirectXコマンド
	std::unique_ptr<DirectXCommand> directXCommand_ = nullptr;

	// DirectXヒープ
	std::unique_ptr<DirectXHeap> directXHeap_ = nullptr;
	
	// DirectXバッファリング
	std::unique_ptr<DirectXBuffering> directXBuffering_ = nullptr;

	// DirectXフェンス
	std::unique_ptr<DirectXFence> directXFence_ = nullptr;

	// DirectX描画
	std::unique_ptr<DirectXDraw> directXDraw_ = nullptr;

	// 深度情報のリソース
	std::unique_ptr<ResourcesDepthStencil> resourceDepthStencil_ = nullptr;



#ifdef _DEBUG

	// DirectXデバッグ
	std::unique_ptr<DirectXDebug> directXDebug_ = nullptr;

#endif
};

