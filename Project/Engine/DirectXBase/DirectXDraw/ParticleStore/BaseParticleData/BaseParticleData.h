#pragma once
#include <list>
#include <cassert>

#include "../../ResourcesData/TransformationResourceDataInstancing/TransformationResourceDataInstancing.h"
#include "Handle/Handle.h"
#include "../../ModelStore/ModelStore.h"
#include "../ParticleInstance/ParticleInstance.h"

// 前方宣言
class MugenEngine;

class BaseParticleData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
		uint32_t numMaxParticle, ParticleHandle particleHandle, std::string* name);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	/// <param name="transformationRootParameterIndex"></param>
	void Register(UINT transformationRootParameterIndex);


	// テクスチャハンドル
	TextureHandle textureHandle_{};

	// モデルハンドル
	ModelHandle modelHandle_{};


	// モデルリソース
	BaseModelResources* modelResource_ = nullptr;

	// パーティクルインスタンスのリスト
	std::list<std::unique_ptr<ParticleInstance>> particles_;

	// 座標変換インスタンシングリソース
	std::unique_ptr<TransformationResourceDataInstancing> transformationResource_ = nullptr;



protected:

	// 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


	// エンジン
	const MugenEngine* engine_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;


	// 最大パーティクル数
	uint32_t numMaxParticle_ = 0;



	// 名前
	std::string* name_ = nullptr;

	// 位置のポインタ
	Vector3* position_ = nullptr;

	// 発生数のポインタ
	uint32_t* perEmission_ = nullptr;

	// 発生頻度のポインタ
	float* emitTime_ = nullptr;



	// 放射タイマー
	float emitTimer_ = 0.0f;


	// パーティクルハンドル
	ParticleHandle particleHandle_{};
};