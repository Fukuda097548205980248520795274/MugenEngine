#pragma once
#include <vector>
#include <cassert>
#include <map>
#include <string>
#include "Math/Vector3/Vector3.h"
#include "Math/Quaternion/Quaternion.h"

// 3次元キーフレーム
struct KeyFrameVector3
{
	// 値
	Vector3 value;

	// 時刻
	float time;
};

// クォータニオンキーフレーム
struct KeyFrameQuaternion
{
	// キーフレームの値
	Quaternion value;

	// 時刻
	float time;
};

struct NodeAnimation
{
	// 移動
	std::vector<KeyFrameVector3> translate;

	// 回転
	std::vector<KeyFrameQuaternion> rotate;

	// 拡縮
	std::vector<KeyFrameVector3> scale;
};

// アニメーション
struct Animation
{
	// アニメーション全体の尺
	float duration;

	// NodeAnimationの集合体
	std::map<std::string, NodeAnimation> nodeAnimations;
};


/// <summary>
/// 任意の時刻の値を取得する
/// </summary>
/// <param name="keyframe"></param>
/// <param name="time"></param>
/// <returns></returns>
Vector3 CalcuateValue(const std::vector<KeyFrameVector3>& keyframe, float time);

/// <summary>
/// 任意の時刻の値を取得する
/// </summary>
/// <param name="keyframe"></param>
/// <param name="time"></param>
/// <returns></returns>
Quaternion CalcuateValue(const std::vector<KeyFrameQuaternion>& keyframe, float time);