#pragma once
#include <fstream>
#include <sstream>
#include <cassert>
#include <list>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "DirectXBase/DirectXDraw/ModelStore/ModelData/ModelData.h"
#include "DirectXBase/DirectXDraw/ModelStore/Animation/Animation.h"

/// <summary>
/// mtlファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

/// <summary>
/// オブジェファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
std::vector<ModelData> LoadObjFile(const std::string& directoryPath, const std::string& filename);

/// <summary>
/// ノードにワールド行列を生成する
/// </summary>
/// <param name="node"></param>
/// <param name="parentWorldMatrix"></param>
void NodeWorldMatrix(Node& node, const Matrix4x4& parentWorldMatrix);

/// <summary>
/// ノード情報を取得する
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Node GetReadNode(const std::string& directoryPath, const std::string& filename);

/// <summary>
/// ノード情報を読む
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
Node ReadNode(aiNode* node);

/// <summary>
/// ノードのワールド行列
/// </summary>
/// <param name="rootNode"></param>
/// <returns></returns>
void GetNodeWorldMatrix(std::vector<Matrix4x4>& worldMatrices, const Node& rootNode);

/// <summary>
/// アニメーションファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename);