#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>
#include "../../BaseMesh/MeshOptions/Transform/Transform.h"
#include "../Animation/Animation.h"
#include "Math/Matrix4x4/Matrix4x4.h"


// ジョイント
struct Joint
{
	// Transform情報
	QuaternionTransform transform;

	// ローカル行列
	Matrix4x4 localMatrix;

	// SkeletonSpaceでの変換行列
	Matrix4x4 skeletonSpaceMatrix;

	// 名前
	std::string name;

	// 子jointのインデックスのリスト
	std::vector<int32_t> children;

	// 自身のインデックス
	int32_t index;

	// 親joint
	std::optional<int32_t> parent;
};

// スケルトン
struct Skeleton
{
	// RootJointのインデックス
	int32_t root;

	// Joint名とインデックスの辞書
	std::map<std::string, int32_t> jointMap;

	// 所属しているjoint
	std::vector<Joint> joints;
};

/// <summary>
/// スケルトンの更新処理
/// </summary>
/// <param name="skeleton"></param>
void UpdateSkeleton(Skeleton& skeleton);

/// <summary>
/// アニメーションを再生する
/// </summary>
/// <param name="skeleton"></param>
/// <param name="animation"></param>
/// <param name="animationTime"></param>
void ApplayAnimation(Skeleton& skeleton, const Animation& animation, float animationTime);