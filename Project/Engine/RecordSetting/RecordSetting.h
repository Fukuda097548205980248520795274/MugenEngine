#pragma once
#include <json.hpp>
#include <variant>
#include <map>
#include <string>
#include <cstdint>
#include <cassert>
#include <fstream>
#include <Windows.h>
#include "Math/Vector2/Vector2.h"
#include "Math/Vector3/Vector3.h"
#include "Math/Vector4/Vector4.h"

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
	/// グループを作成する
	/// </summary>
	/// <param name="groupName"></param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// 項目に値を入れる
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="groupName"></param>
	/// <param name="key"></param>
	/// <param name="value"></param>
	template<typename T>
	void SetValue(const std::string& groupName, const std::string& key, T* value)
	{
		// グループの参照を取得
		Group& group = datas_[groupName];

		// 新しい項目のデータを設定
		Item newItem{};
		newItem = value;

		// 設定した項目を追加
		group[key] = newItem;
	}

	/// <summary>
	/// 登録した調整項目の値に、ファイルの値を反映させる
	/// </summary>
	/// <param name="groupName"></param>
	void RegistGroupDataReflection(const std::string& groupName);


private:

	// シングルトン
	RecordSetting() = default;
	~RecordSetting() = default;
	RecordSetting(RecordSetting&) = delete;
	RecordSetting& operator=(RecordSetting&) = delete;

	/// <summary>
	/// ファイルを記録する
	/// </summary>
	/// <param name="groupName"></param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ファイルを作成する
	/// </summary>
	/// <param name="groupName"></param>
	void CreateRecordFile(const std::string& groupName);

	// インスタンス
	static RecordSetting* instance_;

	// ディレクトリパス
	const std::string& kDirectory = "./Resources/Record/";



	// 項目
	using Item = std::variant<bool*, int32_t*, float*, Vector2*, Vector3*, Vector4*>;

	// グループ
	using Group = std::map<std::string, Item>;

	// 1全データ
	using Datas = std::map<std::string, Group>;

	// 全データ
	Datas datas_;


	// JSON
	using json = nlohmann::json;
};

