#pragma once

#include "Node/Node.h"
#include "AnimationData/AnimationData.h"
#include "SkeletonData/SkeletonData.h"
#include "WeightData/WeightData.h"
#include "Influence/Influence.h"
#include "SkinCluster/SkinCluster.h"

#include "../../DataForGPU/VertexData/VertexData.h"

// マテリアルデータ
struct MaterialData
{
	// テクスチャファイルパス
	std::string textureFilePath;
};

// メッシュデータ
struct MeshData
{
	// インデックスデータ
	std::vector<uint32_t> indices;

	// 頂点データ
	std::vector<VertexDataForGPU> vertices;

	// マテリアルデータ
	MaterialData material;

	// スキンクラスターデータ
	std::map<std::string, JointWeightData> skinClusterData;

	// スキンクラスター
	SkinCluster skinCluster;
};

// モデルデータ
struct ModelData
{
	// メッシュデータ
	std::vector<MeshData> meshData;

	// アニメーション有効化
	bool isAnimation = false;

	// スキニング有効化
	bool isSkinning = false;
};