#include "LoadModel.h"


/// <summary>
/// mtlファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	// ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	// 構築するマテリアルデータ
	MaterialData materialData;

	// 1行
	std::string line;

	while (std::getline(file, line))
	{
		std::string identifier;
		std::stringstream s(line);
		s >> identifier;

		// identifierに応じた処理
		if (identifier == "map_Kd")
		{
			std::string textureFilename;
			s >> textureFilename;

			// 連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
		}
	}

	return materialData;
}

/// <summary>
/// ノード情報を取得する
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Node GetReadNode(const std::string& directoryPath, const std::string& filename, const Matrix4x4& parentMatrix)
{
	// assimpでファイルを開く
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;

	// シーンのデータ
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	return ReadNode(scene->mRootNode, parentMatrix);
}

/// <summary>
/// ノード情報を読む
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
Node ReadNode(aiNode* node,const Matrix4x4& parentMatrix)
{
	// トランスフォームに格納する
	aiVector3D scale, translate;
	aiQuaternion rotate;
	node->mTransformation.Decompose(scale, rotate, translate);

	// 総括
	Node result;

	result.transform.scale = Vector3(scale.x, scale.y, scale.z);

	// 右手 -> 左手
	result.transform.translate = Vector3(-translate.x, translate.y, translate.z);

	// X軸を反転　回転方向が逆なので軸を反転させる
	result.transform.rotate = Quaternion(rotate.x, -rotate.y, -rotate.z, rotate.w);

	// ローカル行列に変換
	result.localMatrix = Make3DAffineMatrix4x4(result.transform.scale, result.transform.rotate, result.transform.translate);

	// ワールド行列を求める
	result.worldMatrix = parentMatrix * result.localMatrix;

	// ノード名を格納
	result.name = node->mName.C_Str();

	// 子供の数だけ確保
	result.children.resize(node->mNumChildren);

	// 再帰的に読んで階層構造を作っていく
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex)
	{
		result.children[childIndex] = ReadNode(node->mChildren[childIndex], result.worldMatrix);
	}

	return result;
}


/// <summary>
/// オブジェファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	// assimpでファイルを開く
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;

	// シーンのデータ
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveRedundantMaterials);

	// メッシュがないのは対応しない
	assert(scene->HasMeshes());

	// モデルデータ
	ModelData modelData;

	// 頂点データ
	Vector4 position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3 normal = Vector3(0.0f, 0.0f, 0.0f);
	Vector2 texcoord = Vector2(0.0f, 0.0f);


	// メッシュ
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
	{
		// メッシュデータ
		MeshData meshData;

		// メッシュのデータ
		aiMesh* mesh = scene->mMeshes[meshIndex];

		// 法線がないメッシュは非対応
		assert(mesh->HasNormals());

		// UV座標がないのは非対応
		assert(mesh->HasTextureCoords(0));


		// メッシュの名前を取得する
		std::string meshName = mesh->mName.C_Str();

		// 頂点データを登録する
		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			// 頂点データを取得する
			aiVector3D& position = mesh->mVertices[i];
			aiVector3D& normal = mesh->mNormals[i];
			aiVector3D& texcoord = mesh->mTextureCoords[0][i];

			// 値を取得する
			VertexDataForGPU vertex;
			vertex.position = Vector4(position.x, position.y, position.z, 1.0f);
			vertex.normal = Vector3(normal.x, normal.y, normal.z);
			vertex.texcoord = Vector2(texcoord.x, texcoord.y);

			// 右手から左手に変換
			vertex.position.x *= -1.0f;
			vertex.normal.x *= -1.0f;

			// データに登録
			meshData.vertices.push_back(vertex);
		}

		// インデックスデータを登録する
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			// フェイスのデータ
			aiFace& face = mesh->mFaces[faceIndex];

			// 三角形のみサポート
			assert(face.mNumIndices == 3);

			// インデックスを登録
			for (uint32_t i = 0; i < face.mNumIndices; ++i)
			{
				meshData.indices.push_back(face.mIndices[i]);
			}
		}


		// マテリアルインデックス
		uint32_t materialIndex = mesh->mMaterialIndex;

		// マテリアルデータ
		aiMaterial* material = scene->mMaterials[materialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
		{
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			meshData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
		}

		// 登録する
		modelData.meshData[meshName] = meshData;
		modelData.meshNames_.push_back(meshName);

		// モデル数をカウントする
		modelData.numMesh++;
	}

	return modelData;
}


/// <summary>
/// gltfファイルからボーン付きのモデルデータを取得する
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
ModelData LoadGltfFileWidthBone(const std::string& directoryPath, const std::string& filename)
{
	// assimpでファイルを開く
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;

	// シーンのデータ
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveRedundantMaterials);

	// メッシュがないのは対応しない
	assert(scene->HasMeshes());

	// モデルデータ
	ModelData modelData;

	// 頂点データ
	Vector4 position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3 normal = Vector3(0.0f, 0.0f, 0.0f);
	Vector2 texcoord = Vector2(0.0f, 0.0f);


	// メッシュ
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
	{
		// メッシュデータ
		MeshData meshData;

		// メッシュのデータ
		aiMesh* mesh = scene->mMeshes[meshIndex];

		// 法線がないメッシュは非対応
		assert(mesh->HasNormals());

		// UV座標がないのは非対応
		assert(mesh->HasTextureCoords(0));


		// メッシュの名前を取得する
		std::string meshName = mesh->mName.C_Str();

		// 頂点データを登録する
		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			// 頂点データを取得する
			aiVector3D& position = mesh->mVertices[i];
			aiVector3D& normal = mesh->mNormals[i];
			aiVector3D& texcoord = mesh->mTextureCoords[0][i];

			// 値を取得する
			VertexDataForGPU vertex;
			vertex.position = Vector4(position.x, position.y, position.z, 1.0f);
			vertex.normal = Vector3(normal.x, normal.y, normal.z);
			vertex.texcoord = Vector2(texcoord.x, texcoord.y);

			// 右手から左手に変換
			vertex.position.x *= -1.0f;
			vertex.normal.x *= -1.0f;

			// データに登録
			meshData.vertices.push_back(vertex);
		}

		// インデックスデータを登録する
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			// フェイスのデータ
			aiFace& face = mesh->mFaces[faceIndex];

			// 三角形のみサポート
			assert(face.mNumIndices == 3);

			// インデックスを登録
			for (uint32_t i = 0; i < face.mNumIndices; ++i)
			{
				meshData.indices.push_back(face.mIndices[i]);
			}
		}


		// ボーンデータを登録する
		for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			// ボーンがあるならスキニングする可能性がある
			modelData.isSkinning = true;

			// ボーンのデータ
			aiBone* bone = mesh->mBones[boneIndex];
			std::string jointName = bone->mName.C_Str();
			JointWeightData& jointWeightData = meshData.skinClusterData[jointName];

			aiMatrix4x4 bindPoseMatrixAssimp = bone->mOffsetMatrix.Inverse();
			aiVector3D scaleAssimp, translateAssimp;
			aiQuaternion rotateAssimp;
			bindPoseMatrixAssimp.Decompose(scaleAssimp, rotateAssimp, translateAssimp);

			// トランスフォームに変える
			Vector3 scale = Vector3(scaleAssimp.x, scaleAssimp.y, scaleAssimp.z);
			Quaternion rotate = Quaternion(rotateAssimp.x, -rotateAssimp.y, -rotateAssimp.z, rotateAssimp.w);
			Vector3 translate = Vector3(-translateAssimp.x, translateAssimp.y, translateAssimp.z);

			// 行列にする
			jointWeightData.inverseBindPoseMatrix = MakeInverseMatrix4x4(Make3DAffineMatrix4x4(scale, rotate, translate));

			// ウェイト
			for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; ++weightIndex)
			{
				jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight , bone->mWeights[weightIndex].mVertexId });
			}
		}


		// マテリアルインデックス
		uint32_t materialIndex = mesh->mMaterialIndex;

		// マテリアルデータ
		aiMaterial* material = scene->mMaterials[materialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
		{
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			meshData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
		}

		// 登録する
		modelData.meshData[meshName] = meshData;
		modelData.meshNames_.push_back(meshName);

		// モデル数をカウントする
		modelData.numMesh++;
	}

	return modelData;
}




/// <summary>
/// ノードのワールド行列
/// </summary>
/// <param name="rootNode"></param>
/// <returns></returns>
void GetNodeWorldMatrix(std::vector<Matrix4x4>& worldMatrices, const Node& rootNode)
{
	worldMatrices.push_back(rootNode.worldMatrix);

	for (const Node& node : rootNode.children)
	{
		GetNodeWorldMatrix(worldMatrices, node);
	}
}


/// <summary>
/// アニメーションファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename, ModelData& modelData)
{
	Animation animation;

	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);

	// アニメーションがないといけいない
	if (scene->mNumAnimations == 0)
	{
		return animation;
	}

	// アニメーションフラグが立つ
	modelData.isAnimation = true;

	// 最初のアニメーションだけ採用
	aiAnimation* animationAssimp = scene->mAnimations[0];

	// 時間の単位を秒に変換
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);

	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex)
	{
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];

		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex)
		{
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];

			KeyFrameVector3 keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// 右手 -> 左手
			keyframe.value = { -keyAssimp.mValue.x, keyAssimp.mValue.y,keyAssimp.mValue.z };
			nodeAnimation.translate.push_back(keyframe);
		}

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex)
		{
			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];

			KeyFrameQuaternion keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// 右手 -> 左手
			keyframe.value = { keyAssimp.mValue.x, -keyAssimp.mValue.y, -keyAssimp.mValue.z , keyAssimp.mValue.w };
			nodeAnimation.rotate.push_back(keyframe);
		}

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; ++keyIndex)
		{
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];

			KeyFrameVector3 keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// そのまま
			keyframe.value = { keyAssimp.mValue.x, keyAssimp.mValue.y,keyAssimp.mValue.z };
			nodeAnimation.scale.push_back(keyframe);
		}
	}

	return animation;
}


/// <summary>
/// スケルトンを作成する
/// </summary>
/// <param name="rootNode"></param>
/// <returns></returns>
Skeleton CreateSkeleton(const Node& rootNode)
{
	Skeleton skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);

	// 名前とインデックスのマッピングを行いアクセスしやすくする
	for (const Joint& joint : skeleton.joints)
	{
		skeleton.jointMap.emplace(joint.name, joint.index);
	}

	// スケルトンを更新する
	UpdateSkeleton(skeleton);

	return skeleton;
}

/// <summary>
/// ジョイントを作成する
/// </summary>
/// <param name="node"></param>
/// <param name="parent"></param>
/// <param name="joints"></param>
/// <returns></returns>
int32_t CreateJoint(const Node& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints)
{
	Joint joint;
	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = MakeIdentityMatrix4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);

	for (const Node& child : node.children)
	{
		// 子jointを作成し、そのインデックスを登録
		int32_t childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].children.push_back(childIndex);
	}

	return joint.index;
}


/// <summary>
/// スキンクラスターを作成する
/// </summary>
/// <param name="device"></param>
/// <param name="skeleton"></param>
/// <param name="modelData"></param>
/// <param name="directXHeap"></param>
/// <returns></returns>
SkinCluster CreateSkinCluster(ID3D12Device* device, const Skeleton& skeleton, const MeshData& meshData,
	DirectXHeap* directXHeap)
{
	SkinCluster skinCluster;


	/*------------------------------
		Palette用のリソースを確保
	------------------------------*/

	skinCluster.paletteResource = CreateBufferResource(device, sizeof(WellForGPU) * skeleton.joints.size());
	WellForGPU* mappedPalette = nullptr;
	skinCluster.paletteResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));

	// spanを使ってアクセスするようにする
	skinCluster.mappedPalette = { mappedPalette, skeleton.joints.size() };
	skinCluster.paletteSrvHandle.first = directXHeap->GetSrvCPUDescriptorHandle();
	skinCluster.paletteSrvHandle.second = directXHeap->GetSrvGPUDescriptorHandle();


	/*--------------------------
		Palette用のSRVを作成
	--------------------------*/

	D3D12_SHADER_RESOURCE_VIEW_DESC paletteSrvDesc{};
	paletteSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	paletteSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	paletteSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	paletteSrvDesc.Buffer.FirstElement = 0;
	paletteSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	paletteSrvDesc.Buffer.NumElements = UINT(skeleton.joints.size());
	paletteSrvDesc.Buffer.StructureByteStride = sizeof(WellForGPU);

	device->CreateShaderResourceView(skinCluster.paletteResource.Get(), &paletteSrvDesc, skinCluster.paletteSrvHandle.first);


	/*-------------------------------
		Influence用のリソースを確保
	-------------------------------*/

	skinCluster.influenceResource = CreateBufferResource(device, sizeof(VertexInfluence) * meshData.vertices.size());
	VertexInfluence* mappedInfluence = nullptr;
	skinCluster.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));

	// 0埋め
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * meshData.vertices.size());
	skinCluster.mappedInfluence = { mappedInfluence, meshData.vertices.size() };


	/*---------------------------
		Influence用のVBVを設定
	---------------------------*/

	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResource->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * meshData.vertices.size());
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	skinCluster.inverseBindPoseMatrices.resize(skeleton.joints.size());
	std::generate(skinCluster.inverseBindPoseMatrices.begin(), skinCluster.inverseBindPoseMatrices.end(), MakeIdentityMatrix4x4);


	/*------------------------------------------
		SkinClusterの情報を解析してInfluenceを格納する
	------------------------------------------*/

	for (const auto& jointWeight : meshData.skinClusterData)
	{
		// skeletonに対象となるjointが含まれているか判断する
		auto it = skeleton.jointMap.find(jointWeight.first);

		// 存在しない名前のJointは後回し
		if (it == skeleton.jointMap.end())
			continue;

		// 該当のIndexのInverseBindPoseMatrixを代入する
		skinCluster.inverseBindPoseMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;

		for (const auto& vertexWeight : jointWeight.second.vertexWeights)
		{
			// 該当のvertexIndexのInfluence情報を参照しておく
			auto& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];

			// 空いているところ (Weight == 0.0f) に入れる
			for (uint32_t index = 0; index < kNumMaxInfluence; ++index)
			{
				if (currentInfluence.weights[index] == 0.0f)
				{
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndices[index] = (*it).second;
					break;
				}
			}
		}
	}


	return skinCluster;
}