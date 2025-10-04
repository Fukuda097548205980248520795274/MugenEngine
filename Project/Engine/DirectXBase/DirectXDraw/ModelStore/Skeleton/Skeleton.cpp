#include "Skeleton.h"

/// <summary>
/// スケルトンの更新処理
/// </summary>
/// <param name="skeleton"></param>
void UpdateSkeleton(Skeleton& skeleton)
{
	// 全てのjointを更新する
	for (Joint& joint : skeleton.joints)
	{
		// ローカル行列
		joint.localMatrix = Make3DAffineMatrix4x4(joint.transform.scale, joint.transform.rotate, joint.transform.translate);

		// 親がいれば行列をかける
		if (joint.parent)
		{
			joint.skeletonSpaceMatrix = joint.localMatrix * skeleton.joints[*joint.parent].skeletonSpaceMatrix;
		}
		else
		{
			// 親がいないので、ローカル行列とSkeletonSpaceMatrixは一致する
			joint.skeletonSpaceMatrix = joint.localMatrix;
		}
	}
}

/// <summary>
/// アニメーションを再生する
/// </summary>
/// <param name="skeleton"></param>
/// <param name="animation"></param>
/// <param name="animationTime"></param>
void ApplayAnimation(Skeleton& skeleton, const Animation& animation, float animationTime)
{
	for (Joint& joint : skeleton.joints)
	{
		// 対象のjointのアニメーションがあれば、値の適用を行う
		if (auto it = animation.nodeAnimations.find(joint.name); it != animation.nodeAnimations.end())
		{
			const NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.translate = CalcuateValue(rootNodeAnimation.translate, animationTime);
			joint.transform.rotate = CalcuateValue(rootNodeAnimation.rotate, animationTime);
			joint.transform.scale = CalcuateValue(rootNodeAnimation.scale, animationTime);
		}
	}
}