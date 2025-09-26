#pragma once
#include <string>
#include <vector>

#include "../../DataForGPU/VertexData/VertexData.h"

// マテリアルデータ
struct MaterialData
{
	// テクスチャファイルパス
	std::string textureFilePath;
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
};