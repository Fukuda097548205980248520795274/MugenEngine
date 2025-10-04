#pragma once
#include <string>
#include <vector>
#include <map>
#include <span>
#include <array>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "../../DataForGPU/VertexData/VertexData.h"
#include "Math/Matrix4x4/Matrix4x4.h"
#include "../../BaseMesh/MeshOptions/Transform/Transform.h"

#include "../Skeleton/Skeleton.h"

// マテリアルデータ
struct MaterialData
{
	// テクスチャファイルパス
	std::string textureFilePath;
};

// ノード
struct Node
{
	// クォータニオントランスフォーム
	QuaternionTransform transform;

	// ローカル行列
	Matrix4x4 localMatrix;

	// ワールド行列
	Matrix4x4 worldMatrix;

	// 名前
	std::string name;

	// 子
	std::vector<Node> children;
};

// 頂点ウェイトデータ
struct VertexWeightData
{
	float weight;
	uint32_t vertexIndex;
};

// ジョイントウェイトデータ
struct JointWeightData
{
	Matrix4x4 inverseBindPoseMatrix;
	std::vector<VertexWeightData> vertexWeights;
};

// インフルエンスの最大数
const uint32_t kNumMaxInfluence = 4;

// 頂点インフルエンス
struct VertexInfluence
{
	std::array<float, kNumMaxInfluence> weights;
	std::array<int32_t, kNumMaxInfluence> jointIndices;
};

// GPUに送るウェル
struct WellForGPU
{
	// 位置用
	Matrix4x4 skeletonSpaceMatrix;

	// 法線用
	Matrix4x4 skeletonSpaceInverseTransposeMatrix;
};

// スキンクラスター
struct SkinCluster
{
	std::vector<Matrix4x4> inverseBindPoseMatrices;

	Microsoft::WRL::ComPtr<ID3D12Resource> influenceResource;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView;
	std::span<VertexInfluence> mappedInfluence;

	Microsoft::WRL::ComPtr<ID3D12Resource> paletteResource;
	std::span<WellForGPU> mappedPalette;
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> paletteSrvHandle;
};


// モデルデータ
struct ModelData
{
	// インデックスデータ
	std::vector<uint32_t> indices;

	// 頂点データ
	std::vector<VertexDataForGPU> vertices;

	// マテリアルデータ
	MaterialData material;

	// スキンクラスターデータ
	std::map<std::string, JointWeightData> skinClusterData;
};

/// <summary>
/// スキンクラスターの更新処理
/// </summary>
/// <param name="skinCluster"></param>
/// <param name="skeleton"></param>
void UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton);