#pragma once
#include <list>
#include <memory>
#include <string>
#include "../Camera/Camera3D/Camera3D.h"
#include "Particle/Particle.h"

// 前方宣言
class MugenEngine;

class ParticleEmitter
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera3d"></param>
	void Initialize(const MugenEngine* engine, const Camera3D* camera3d,const std::string& name, uint32_t maxNumParticles, const Vector3& center,
		uint32_t count, float emitTime);

	/// <summary>
	/// 放出処理
	/// </summary>
	void Emit();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 名前のGetter
	/// </summary>
	/// <returns></returns>
	std::string GetName()const { return name_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// カメラ3D
	const Camera3D* camera3d_ = nullptr;


	// 名前
	std::string name_;

	// パーティクルのリスト
	std::list<std::unique_ptr<Particle>> particles_;

	// パーティクルの最大数
	uint32_t maxNumParticles_ = 0;


	// 中心点
	Vector3 center_;


	// 発生数
	uint32_t count_ = 0;

	// 放出タイマー
	float emitTimer_ = 0.0f;

	// 放出時間
	float emitTime_ = 0.0f;
};

