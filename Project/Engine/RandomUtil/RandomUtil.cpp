#include "RandomUtil.h"

// インスタンス
RandomUtil* RandomUtil::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
RandomUtil* RandomUtil::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new RandomUtil();
	}

	return instance_;
}

/// <summary>
/// 初期化
/// </summary>
void RandomUtil::Initialize()
{
	// 乱数生成器の初期化
	randomEngine_.seed(seedGenerator_());
}

/// <summary>
/// 終了処理
/// </summary>
void RandomUtil::Finalize()
{
	delete instance_;
	instance_ = nullptr;
}