#pragma once
#include <random>

class RandomUtil
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static RandomUtil* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 範囲で乱数を取得する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	template<typename T>
	T GetRandomRange(T min, T max)
	{
		// int型
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> dist(min, max);
			return dist(randomEngine_);
		} 
		else if constexpr (std::is_floating_point_v<T>)
		{
			// float double 型
			std::uniform_real_distribution<T> dist(min, max);
			return dist(randomEngine_);
		}
		else
		{
			// それ以外はエラー
			static_assert(false, "Unsupported type for random range");
		}

	}


private:

	// シングルトン
	RandomUtil() = default;
	~RandomUtil() = default;
	RandomUtil(RandomUtil&) = delete;
	RandomUtil& operator=(RandomUtil&) = delete;

	// インスタンス
	static RandomUtil* instance_;

	
	// 乱数生成器
	std::random_device seedGenerator_;

	// ランダムエンジン
	std::mt19937 randomEngine_;
};

