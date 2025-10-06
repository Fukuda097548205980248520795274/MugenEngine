#pragma once
#include <string>
#include <vector>

#include "../../DataForGPU/VertexData/VertexData.h"
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// マテリアルデータ
struct MaterialData
{
	// テクスチャファイルパス
	std::string textureFilePath;
};

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
};

// モデルデータ
struct ModelData
{
	// メッシュデータ
	std::vector<MeshData> meshData;
};