#pragma once
#include "../../../Camera/Camera3D/Camera3D.h"
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
	void Initliaze(const MugenEngine* engine,const Camera3D* camera3d, uint32_t numMaxParticle, ModelHandle modelHandle, const std::string& name);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="particleHandle"></param>
	void Initliaze(const MugenEngine* engine, const Camera3D* camera3d, ParticleHandle particleHandle);

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
	/// 名前のGetter
	/// </summary>
	/// <returns></returns>
	std::string* GetNameP() { return &name_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// 3Dカメラ
	const Camera3D* camera3d_ = nullptr;



	// 最大パーティクル数
	uint32_t numMaxParticle_ = 0;

	// 名前
	std::string name_{};



	// モデルハンドル
	ModelHandle modelHandle_{};

	// パーティクルハンドル
	ParticleHandle particleHandle_{};
};

