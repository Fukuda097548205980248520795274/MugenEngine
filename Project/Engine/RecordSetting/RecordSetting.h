#pragma once
#include <variant>
#include <map>
#include <string>
#include <cstdint>
#include "Math/Vector2/Vector2.h"
#include "Math/Vector3/Vector3.h"
#include "Math/Vector4/Vector4.h"
#include "Math/Quaternion/Quaternion.h"

#include "../../../Externals/ImGui/imgui.h"
#include "../../../Externals/ImGui/imgui_impl_dx12.h"
#include "../../../Externals/ImGui/imgui_impl_win32.h"

class RecordSetting
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static RecordSetting* GetInstance();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// グループの作成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);


	/// <summary>
	/// 項目の設定
	/// </summary>
	/// <param name="groupName"></param>
	/// <param name="key"></param>
	/// <param name="value"></param>
	template<typename T>
	void SetValue(const std::string& groupName, const std::string& key, T value)
	{
		// グループの参照を取得
		Group& group = datas_[groupName];

		// 新しい項目のデータを設定
		Item newItem{};
		newItem = value;

		// 設定した項目をmapに追加
		group[key] = newItem;
	}


private:

	// 静的メンバ変数のポインタ
	static RecordSetting* instance_;

	// コンストラクタなどを使えないようにする
	RecordSetting() = default;
	~RecordSetting() = default;
	RecordSetting(RecordSetting&) = delete;
	RecordSetting& operator=(RecordSetting&) = delete;


	// スライダー項目
	using Item = std::variant<bool, int32_t, float, Vector2, Vector3, Vector4, Quaternion>;

	// グループ
	using Group = std::map<std::string, Item>;

	// 全データ
	using Datas = std::map<std::string, Group>;


	// 全データ
	Datas datas_;
};

