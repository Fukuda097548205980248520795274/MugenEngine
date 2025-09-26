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

	/// <summary>
	/// モデルを読み込む
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	uint32_t LoadModel(const std::string& directory, const std::string& fileName) { return directXDraw_->LoadModel(directory, fileName); }

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert)
	{
		directXDraw_->DrawMode(worldTransform, uvTransform, camera, modelHandle, color, enableLighting, enableHalfLanbert);
	}

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
		const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color)
	{
		directXDraw_->DrawSprite(p0, p1, p2, p3, uvTransform, camera, textureHandle, color);
	}

	/// <summary>
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode) { directXDraw_->SetBlendModePrimitive(blendMode); }

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert, int32_t segment, int32_t ring)
	{
		directXDraw_->DrawUVSphere(worldTransform, uvTransform, camera, textureHandle, color, enableLighting, enableHalfLanbert, segment, ring);
	}

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
		const Vector4& color, bool enableLighting, bool enableHalfLanbert)
	{
		directXDraw_->DrawCube(worldTransform, uvTransform, camera, textureHandle, color, enableLighting, enableHalfLanbert);
	}

	
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

