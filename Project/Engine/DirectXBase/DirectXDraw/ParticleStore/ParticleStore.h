#pragma once

class ParticleStore
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static ParticleStore* GetInstance();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();


private:

	// シングルトン
	ParticleStore() = default;
	~ParticleStore() = default;
	ParticleStore(ParticleStore&) = delete;
	ParticleStore& operator=(ParticleStore&) = delete;

	// インスタンス
	static ParticleStore* instance_;
};

