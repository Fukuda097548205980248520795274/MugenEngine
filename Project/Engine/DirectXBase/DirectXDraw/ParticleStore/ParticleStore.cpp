#include "ParticleStore.h"

// インスタンス
ParticleStore* ParticleStore::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
ParticleStore* ParticleStore::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ParticleStore();
	}

	return instance_;
}

/// <summary>
/// 終了処理
/// </summary>
void ParticleStore::Finalize()
{
	delete instance_;
}