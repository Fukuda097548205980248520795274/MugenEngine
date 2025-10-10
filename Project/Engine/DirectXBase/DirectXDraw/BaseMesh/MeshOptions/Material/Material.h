#pragma once
#define NOMINMAX
#include <algorithm>
#include "../../../../../Math/Vector4/Vector4.h"

class Material
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	// 色
	Vector4 color_{};


	// ライティング有効化
	bool enableLighting_ = true;

	// ハーフランバート有効化
	bool enableHalfLambert_ = true;


	// スペキュラー有効化
	bool enableSpecular_ = false;

	// ブリンフォン有効化
	bool enableBlinnPhong_ = false;

	// 光沢度
	float shininess_ = 25.0f;
};

