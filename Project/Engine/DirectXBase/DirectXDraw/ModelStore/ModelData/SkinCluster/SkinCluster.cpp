#include "SkinCluster.h"

/// <summary>
/// スキンクラスターの更新処理
/// </summary>
/// <param name="skinCluster"></param>
/// <param name="skeleton"></param>
void UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton)
{
	for (size_t jointIndex = 0; jointIndex < skeleton.joints.size(); ++jointIndex)
	{
		assert(jointIndex < skinCluster.inverseBindPoseMatrices.size());

		skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix =
			skinCluster.inverseBindPoseMatrices[jointIndex] * skeleton.joints[jointIndex].skeletonSpaceMatrix;

		skinCluster.mappedPalette[jointIndex].skeletonSpaceInverseTransposeMatrix =
			MakeTransposeMatrix4x4(MakeInverseMatrix4x4(skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix));
	}
}