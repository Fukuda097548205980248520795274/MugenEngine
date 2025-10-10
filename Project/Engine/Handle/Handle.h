#pragma once
#include <cstdint>

// テクスチャハンドル
struct TextureHandle
{
	uint32_t value;
};

// モデルハンドル
struct ModelHandle
{
	uint32_t value;
};

// サウンドハンドル
struct SoundHandle
{
	uint32_t value;
};

// プレイハンドル
struct PlayHandle
{
	uint32_t value;

	// 使用しているかどうか
	bool IsUse() { return value == 0 ? true : false; }
};