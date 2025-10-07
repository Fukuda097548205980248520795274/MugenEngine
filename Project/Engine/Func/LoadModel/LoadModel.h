#pragma once
#include <fstream>
#include <sstream>
#include <cassert>
#include <list>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "DirectXBase/DirectXDraw/ModelStore/ModelData/ModelData.h"
#include "DirectXBase/DirectXHeap/DirectXHeap.h"
#include "Func/CreateBufferResource/CreateBufferResource.h"

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
ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

/// <summary>
/// gltfファイルからボーン付きのモデルデータを取得する
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
ModelData LoadGltfFileWidthBone(const std::string& directoryPath, const std::string& filename);


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
Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename, ModelData& modelData);


/// <summary>
/// スケルトンを作成する
/// </summary>
/// <param name="rootNode"></param>
/// <returns></returns>
Skeleton CreateSkeleton(const Node& rootNode);

/// <summary>
/// ジョイントを作成する
/// </summary>
/// <param name="node"></param>
/// <param name="parent"></param>
/// <param name="joints"></param>
/// <returns></returns>
int32_t CreateJoint(const Node& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

/// <summary>
/// スキンクラスターを作成する
/// </summary>
/// <param name="device"></param>
/// <param name="skeleton"></param>
/// <param name="modelData"></param>
/// <param name="directXHeap"></param>
/// <returns></returns>
SkinCluster CreateSkinCluster(ID3D12Device* device, const Skeleton& skeleton, const MeshData& meshData,
	DirectXHeap* directXHeap);