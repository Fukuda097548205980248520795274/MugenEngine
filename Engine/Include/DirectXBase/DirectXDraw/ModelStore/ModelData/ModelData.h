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
	// 頂点データ
	std::vector<VertexDataModelForGPU> vertices;

	// マテリアルデータ
	MaterialData material;
};