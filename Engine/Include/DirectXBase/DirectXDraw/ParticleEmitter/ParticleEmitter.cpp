#include "ParticleEmitter.h"
#include "../../../MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
void ParticleEmitter::Initialize(const MugenEngine* engine, const Camera3D* camera3d, const std::string& name, uint32_t maxNumParticles, uint32_t textureHandle,
	const Vector3& center, uint32_t count, float emitTime)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	maxNumParticles_ = maxNumParticles;
	textureHandle_ = textureHandle;
	center_ = center;
	count_ = count;
	emitTime_ = emitTime;
}

/// <summary>
/// 放出処理
/// </summary>
void ParticleEmitter::Emit()
{
	// タイマーを進める
	emitTimer_ += engine_->GetDeltaTime();
	emitTimer_ = std::min(emitTimer_, emitTime_);

	// タイマーを越えたらパーティクル放出準備
	if (emitTimer_ >= emitTime_)
	{
		for (uint32_t num = 0; num < count_; ++num)
		{
			// 放出したらタイマーを初期化する
			emitTimer_ = 0.0f;

			// 最大数を越えたら放出しない
			if (particles_.size() >= maxNumParticles_)
				break;

			std::unique_ptr<Particle> particle = std::make_unique<Particle>();
			particle->Initialize(engine_, Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), center_, 3.0f, Vector3(1.0f, 0.0f, 0.0f), 1.0f);

			particles_.push_back(std::move(particle));
		}
	}
}

/// <summary>
/// 更新処理
/// </summary>
void ParticleEmitter::Update()
{
	// パーティクルの更新処理
	for (std::unique_ptr<Particle>& particle : particles_)
	{
		particle->Update();
	}

	// 終了したパーティクルを削除する
	particles_.remove_if([](std::unique_ptr<Particle>& particle)
		{
			if (particle->IsFinished())
			{
				return true;
			}
			return false;
		}
	);
}