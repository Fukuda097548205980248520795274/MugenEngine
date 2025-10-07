#pragma once
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <optional>

#include "Math/Vector3/Vector3.h"
#include "Math/Matrix4x4/Matrix4x4.h"
#include "Math/Quaternion/Quaternion.h"
#include "../../../BaseMesh/MeshOptions/Transform/Transform.h"
#include "../AnimationData/AnimationData.h"

// ジョイント
struct Joint
{
	// Transform情報
	QuaternionTransform3D transform;

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
/// ボーンのアニメーションを再生する
/// </summary>
/// <param name="skeleton"></param>
/// <param name="animation"></param>
/// <param name="animationTime"></param>
void ApplayBoneAnimation(Skeleton& skeleton, const Animation& animation, float animationTime);