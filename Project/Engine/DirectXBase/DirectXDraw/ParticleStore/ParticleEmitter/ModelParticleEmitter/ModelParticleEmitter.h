#pragma once
#include "Math/Vector3/Vector3.h"
#include "Handle/Handle.h"
#include <string>

// 前方宣言
class MugenEngine;

class ModelParticleEmitter
{
public:


	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="numMaxParticle"></param>
	void Initliaze(const MugenEngine* engine, uint32_t numMaxParticle, ModelHandle modelHandle, const std::string& name);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="particleHandle"></param>
	void Initliaze(const MugenEngine* engine, ParticleHandle particleHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクルハンドルのSetter
	/// </summary>
	/// <param name="particleHandle"></param>
	void SetParticleHandle(ParticleHandle particleHandle) { particleHandle_ = particleHandle; }

	/// <summary>
	/// 最大パーティクル数のGetter
	/// </summary>
	/// <returns></returns>
	uint32_t GetNumMaxParticle()const { return numMaxParticle_; }

	/// <summary>
	/// モデルハンドルのGetter
	/// </summary>
	/// <returns></returns>
	ModelHandle GetModelHandle()const { return modelHandle_; }


	/// <summary>
	/// 位置のポインタのGetter
	/// </summary>
	/// <returns></returns>
	Vector3* GetPositionP() { return &position_; }

	/// <summary>
	/// 放出数のポインタのGetter
	/// </summary>
	/// <returns></returns>
	uint32_t* GetEmitNumP() { return &emitNum_; }

	/// <summary>
	/// 放出時間のポインタのGetter
	/// </summary>
	/// <returns></returns>
	float* GetEmitTimeP() { return &emitTime_; }

	/// <summary>
	/// 名前のポインタのGetter
	/// </summary>
	/// <returns></returns>
	std::string* GetNameP() { return &name_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;



	// 最大パーティクル数
	uint32_t numMaxParticle_ = 0;

	// 名前
	std::string name_{};


	// 位置
	Vector3 position_ = Vector3(0.0f, 0.0f, 0.0f);

	// 一度に放出する数
	uint32_t emitNum_ = 1;

	// 発生頻度
	float emitTime_ = 0.0f;



	// モデルハンドル
	ModelHandle modelHandle_{};

	// パーティクルハンドル
	ParticleHandle particleHandle_{};
};

