#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

class Camera3D
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	void Initialize(int32_t screenWidth, int32_t screenHeight);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 親ワールド行列のSetter
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const Matrix4x4* parent) { parent_ = parent; }

	/// <summary>
	/// ワールド座標のGetter
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition() const;


	// 拡縮
	Vector3 scale_;

	// 回転
	Vector3 rotation_;

	// 移動
	Vector3 translation_;


	// ワールド行列
	Matrix4x4 worldMatrix_;

	// ビュー行列
	Matrix4x4 viewMatrix_;

	// 正射影行列
	Matrix4x4 projectionMatrix_;


	// 画角
	float fov_ = 0.45f;

	// 画面の横幅
	float screenWidth_ = 0.0f;

	// 画面の縦幅
	float screenHeight_ = 0.0f;

	// 近平面
	float nearClip_ = 0.1f;

	// 遠平面
	float farClip_ = 800.0f;


private:

	// 親ワールド行列
	const Matrix4x4* parent_ = nullptr;
};

