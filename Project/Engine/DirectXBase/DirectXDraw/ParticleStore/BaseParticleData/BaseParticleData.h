#pragma once
#include <list>
#include <cassert>

#include "../../ResourcesData/ParticleDataInstancing/ParticleDataInstancing.h"
#include "Handle/Handle.h"
#include "../../ModelStore/ModelStore.h"
#include "../ParticleInstance/ParticleInstance.h"
#include "Func/Random/Random.h"

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

	/// <summary>
	/// パーティクルハンドルのGetter
	/// </summary>
	/// <returns></returns>
	ParticleHandle GetParticleHandle()const { return particleHandle_; }

	/// <summary>
	/// 名前のGetter
	/// </summary>
	/// <returns></returns>
	const std::string& GetName()const { return *name_; }


	/// <summary>
	/// エミッターの位置のSetter
	/// </summary>
	/// <param name="position"></param>
	void SetEmitterPosition(const Vector3& position) { *position_ = position; }



	// テクスチャハンドル
	TextureHandle textureHandle_{};

	// モデルハンドル
	ModelHandle modelHandle_{};


	// モデルリソース
	BaseModelResources* modelResource_ = nullptr;

	// パーティクルインスタンスのリスト
	std::list<std::unique_ptr<ParticleInstance>> particles_;

	// 座標変換インスタンシングリソース
	std::unique_ptr<ParticleDataInstancing> particleResourcesInstancing_ = nullptr;


	// 範囲の指定
	enum class RANGETYPE
	{
		AABB,
		SPHERE
	};



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

	// 発生範囲
	Vector3* emitRange_ = nullptr;

	// 球体有効化
	RANGETYPE* enableSphere_ = nullptr;


	// 発生数のポインタ
	uint32_t* perEmission_ = nullptr;

	// 発生頻度のポインタ
	float* emitTime_ = nullptr;


	// サイズの範囲
	Vector2* sizeRange_ = nullptr;

	// 最終的なサイズ
	float* sizeFinal_ = nullptr;


	// 速度の範囲
	Vector2* speedRange_ = nullptr;

	// 最終的な速度
	float* speedFinal_ = nullptr;


	// 放出時間の範囲
	Vector2* releasedTimeRange_ = nullptr;


	// 最初の色
	Vector4* colorStart_ = nullptr;

	// 最終的な色
	Vector4* colorFinal_ = nullptr;


	// 重力方向
	Vector3* gravityDirection_ = nullptr;

	// 重力加速度
	float* gravityAcceleration_ = nullptr;



	// 放射タイマー
	float emitTimer_ = 0.0f;


	// パーティクルハンドル
	ParticleHandle particleHandle_{};
};