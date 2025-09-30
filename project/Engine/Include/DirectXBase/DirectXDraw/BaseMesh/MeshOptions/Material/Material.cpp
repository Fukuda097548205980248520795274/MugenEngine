#include "Material.h"

/// <summary>
/// 初期化
/// </summary>
void Material::Initialize()
{
	// 初期の色
	color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

/// <summary>
/// 更新処理
/// </summary>
void Material::Update()
{
	// 光沢度の制限
	shininess_ = std::max(shininess_, 1.0f);
}