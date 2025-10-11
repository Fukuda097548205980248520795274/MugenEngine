#pragma once
#include <chrono>
#include <thread>

#include "DirectXDevice/DirectXDevice.h"
#include "DirectXCommand/DirectXCommand.h"
#include "DirectXHeap/DirectXHeap.h"
#include "DirectXBuffering/DirectXBuffering.h"
#include "DirectXDebug/DirectXDebug.h"
#include "../Func/DirectXTransitionBarrier/DirectXTransitionBarrier.h"
#include "DirectXFence/DirectXFence.h"
#include "DirectXDraw/DirectXDraw.h"
#include "ResourcesDepthStencil/ResourcesDepthStencil.h"
#include "WinApp/WinApp.h"
#include "DirectXBase/ImGuiRender/ImGuiRender.h"

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
	void Initialize(LogFile* logFile, const WinApp* winApp, const int32_t* kClientWidth, const int32_t* kClientHeight);

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
	TextureHandle LoadTexture(const std::string& filePath) { return directXDraw_->LoadTexture(filePath); }

	/// <summary>
	/// テクスチャの横幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureWidth(TextureHandle handle)const { return directXDraw_->GetTextureWidth(handle); }

	/// <summary>
	/// テクスチャの縦幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureHeight(TextureHandle handle)const { return directXDraw_->GetTextureHeight(handle); }

	/// <summary>
	/// モデルを読み込む
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	ModelHandle LoadModel(const std::string& directory, const std::string& fileName) { return directXDraw_->LoadModel(directory, fileName); }

	/// <summary>
	/// アニメーションフラグのGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	bool IsAnimation(ModelHandle handle)const { return directXDraw_->IsAnimation(handle); }

	/// <summary>
	/// アニメーション時間のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	float GetAnimationDuration(ModelHandle handle)const { return directXDraw_->GetAnimationDuration(handle); }


	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	ParticleHandle LoadParticleEmitter(BillboardParticleEmitter* particleEmitter) { return directXDraw_->LoadParticleEmitter(particleEmitter); }

	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	ParticleHandle LoadParticleEmitter(ModelParticleEmitter* particleEmitter) { return directXDraw_->LoadParticleEmitter(particleEmitter); }

	/// <summary>
	/// 登録したパーティクルの更新処理
	/// </summary>
	/// <param name="particleHandle"></param>
	void UpdateRegistParticle(ParticleHandle particleHandle) { directXDraw_->UpdateRegistParticle(particleHandle); }


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
	void DrawModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, ModelHandle modelHandle,
		const Material* material, float animationTimer)
	{
		directXDraw_->DrawModel(worldTransform, uvTransform, camera, modelHandle, material, animationTimer);
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
	void DrawSprite(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,const Vector2& textureLeftTop, const Vector2& textureSize,
		const UVTransform* uvTransform, const Camera2D* camera, TextureHandle textureHandle, const Vector4& color)
	{
		directXDraw_->DrawSprite(p0, p1, p2, p3, textureLeftTop, textureSize, uvTransform, camera, textureHandle, color);
	}

	/// <summary>
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode) { directXDraw_->SetBlendModePrimitive(blendMode); }

	/// <summary>
	/// 平面を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="material"></param>
	void DrawPlane(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material)
	{
		directXDraw_->DrawPlane(worldTransform, uvTransform, camera, textureHandle, material);
	}

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
	void DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material, int32_t segment, int32_t ring)
	{
		directXDraw_->DrawUVSphere(worldTransform, uvTransform, camera, textureHandle, material, segment, ring);
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
	void DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material)
	{
		directXDraw_->DrawCube(worldTransform, uvTransform, camera, textureHandle, material);
	}



	/// <summary>
	/// ビルボードパーティクルを描画する
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="camera"></param>
	void DrawBillboardParticle(ParticleHandle particleHandle, const Camera3D* camera) { directXDraw_->DrawBillboardParticle(particleHandle, camera); }
	
private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// ウィンドウハンドル
	const WinApp* winApp_ = nullptr;

	// 画面の横幅
	const int32_t* kClientWidth_ = nullptr;

	// 画面の縦幅
	const int32_t* kClientHeight_ = nullptr;


	/// <summary>
	/// FPS固定初期化
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS固定更新処理
	/// </summary>
	void UpdateFixFPS();

	// 記録時間（FPS固定用）
	std::chrono::steady_clock::time_point reference_;



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


#ifdef _DEVELOPMENT
	// ImGui描画システム
	std::unique_ptr<ImGuiRender> imGuiRender_ = nullptr;
#endif

	
#ifdef _DEBUG
	// DirectXデバッグ
	std::unique_ptr<DirectXDebug> directXDebug_ = nullptr;
#endif
};

