#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"
#include "../../../../Math/Vector2/Vector2.h"

class Camera2D
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	// 拡縮
	Vector2 scale_;

	// 回転
	float rotation_;

	// 移動
	Vector2 translation_;


	// ワールド行列
	Matrix4x4 worldMatrix_;

	// ビュー行列
	Matrix4x4 viewMatrix_;

	// 正射影行列
	Matrix4x4 projectionMatrix_;


	// 画面の横幅
	float screenWidth_ = 0.0f;

	// 画面の縦幅
	float screenHeight_ = 0.0f;
};