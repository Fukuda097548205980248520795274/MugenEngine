#pragma once
#include <string>
#include <vector>
#include "Math/Matrix4x4/Matrix4x4.h"
#include "../../../BaseMesh/MeshOptions/Transform/Transform.h"

// ノード
struct Node
{
	// ローカル行列
	Matrix4x4 localMatrix;

	// ワールド行列
	Matrix4x4 worldMatrix;

	// 名前
	std::string name;

	// 子
	std::vector<Node> children;


	// クォータニオン用のトランスフォーム
	QuaternionTransform3D transform;
};