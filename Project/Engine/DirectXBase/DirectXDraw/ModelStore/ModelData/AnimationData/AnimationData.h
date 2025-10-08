#pragma once
#include <string>
#include <vector>
#include <map>
#include <assert.h>

#include "Math/Vector3/Vector3.h"
#include "Math/Quaternion/Quaternion.h"

// キーフレーム
template<typename Tvalue>
struct KeyFrame
{
	// 値
	Tvalue value;

	// 時刻
	float time;
};


// 3次元用のキーフレーム
using KeyFrameVector3 = KeyFrame<Vector3>;

// クォータニオン用のキーフレーム
using KeyFrameQuaternion = KeyFrame<Quaternion>;


// ノードアニメーション
struct NodeAnimation
{
	// 位置
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
	float duration = 0.0f;

	// ノードアニメーションの集合体
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