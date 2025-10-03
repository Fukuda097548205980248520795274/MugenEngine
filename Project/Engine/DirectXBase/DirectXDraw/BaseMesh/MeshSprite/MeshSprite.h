#pragma once
#include <memory>
#include "../MeshOptions/WorldTransform2D/WorldTransform2D.h"
#include "../MeshOptions/UVTransform/UVTransform.h"
#include "../../Camera/Camera2D/Camera2D.h"

// 前方宣言
class MugenEngine;

class MeshSprite
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera2d"></param>
	/// <param name="textureHandle"></param>
	void Initialize(const MugenEngine* engine, const Camera2D* camera2d, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// テクスチャハンドルのSetter
	/// </summary>
	/// <param name="textureHandle"></param>
	void SetTextureHandle(uint32_t textureHandle) { textureHandle_ = textureHandle; }

	/// <summary>
	/// X方向をフリップする
	/// </summary>
	/// <param name="isFlip"></param>
	void FlipX(bool isFlip) { isFlipX_ = isFlip; }

	/// <summary>
	/// Y方向をフリップする
	/// </summary>
	/// <param name="isFlip"></param>
	void FlipY(bool isFlip) { isFlipY_ = isFlip; }


	/// <summary>
	/// テクスチャ左上のGetter
	/// </summary>
	/// <returns></returns>
	Vector2 GetTextureLeftUp()const { return textureLeftTop_; }

	/// <summary>
	/// テクスチャ左上のSetter
	/// </summary>
	/// <param name="textureLeftTop"></param>
	void SetTextureLeftUp(Vector2 textureLeftTop) { textureLeftTop_ = textureLeftTop; }

	/// <summary>
	/// テクスチャ切り出しサイズのGetter
	/// </summary>
	/// <returns></returns>
	Vector2 GetTextureSize()const { return textureSize_; }

	/// <summary>
	/// テクスチャ切り出しサイズのSetter
	/// </summary>
	/// <param name="textureSize"></param>
	void SetTextureSize(Vector2 textureSize) { textureSize_ = textureSize; }


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform2D> worldTransform_ = nullptr;

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = nullptr;

	// アンカーポイント
	Vector2 anchor_ = Vector2(0.0f, 0.0f);

	// 色
	Vector4 color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ
	const Camera2D* camera2d_ = nullptr;


	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 左右フリップ
	bool isFlipX_ = false;

	// 上下フリップ
	bool isFlipY_ = false;

	// テクスチャ座標左上
	Vector2 textureLeftTop_ = { 0.0f, 0.0f };

	// テクスチャ切り出しサイズ
	Vector2 textureSize_{ 0.0f, 0.0f };
};

