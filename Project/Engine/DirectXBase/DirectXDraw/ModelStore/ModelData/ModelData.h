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

	// メッシュ番号
	uint32_t meshNumber_;
};

// モデルデータ
struct ModelData
{
	// メッシュデータ
	std::map<std::string, MeshData> meshData;

	// メッシュの名前
	std::vector<std::string> meshNames_;

	// メッシュ数
	uint32_t numMesh = 0;

	// アニメーション有効化
	bool isAnimation = false;

	// スキニング有効化
	bool isSkinning = false;
};