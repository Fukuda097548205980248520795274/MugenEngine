#pragma once

// ブレンドモード
enum class BlendMode
{
	// 合成なし
	kNone,

	// ノーマル
	kNormal,

	// 加算合成
	kAdd,

	// 減算合成
	kSubtract,

	// 乗算合成
	kMultiply,

	// スクリーン合成
	kScreen,

	kNumBlendMode
};
