#include "Particle.h"
#include "../../../../MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void Particle::Initialize(const MugenEngine* engine, const Vector3& scale, const Vector3& rotation, const Vector3& translation,
	float speed, const Vector3& velocity, float lifeTime)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	transform_.scale = scale;
	transform_.rotation = rotation;
	transform_.translation = translation;
	speed_ = speed;
	velocity_ = velocity;
	lifeTime_ = lifeTime;
}

/// <summary>
/// 更新処理
/// </summary>
void Particle::Update()
{
	// 移動させる
	transform_.translation += (velocity_ * speed_) * engine_->GetDeltaTime();

	// タイマーを進める
	lifeTimer_ += engine_->GetDeltaTime();

	// 時間を越えたら終了する
	if (lifeTimer_ >= lifeTime_)
	{
		IsFinished_ = true;
		return;
	}
}