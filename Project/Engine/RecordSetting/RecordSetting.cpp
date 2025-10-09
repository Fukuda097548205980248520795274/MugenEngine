#include "RecordSetting.h"


RecordSetting* RecordSetting::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
RecordSetting* RecordSetting::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new RecordSetting();
	}

	return instance_;
}

/// <summary>
/// 更新処理
/// </summary>
void RecordSetting::Update()
{
#ifdef _DEBUG

	/*

	if (!ImGui::Begin("RecordSetting"), nullptr, ImGuiWindowFlags_MenuBar)
	{
		ImGui::End();
		return;
	}
	if (!ImGui::BeginMenuBar()) return;


	// 各グループについて
	for (Datas::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup)
	{
		// グループ名を取得
		const std::string& groupName = itGroup->first;

		// グループの参照
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;


		// 各項目について
		for (Group::iterator itItem = group.begin(); itItem != group.end(); ++itItem)
		{
			// 項目名を取得
			const std::string& itemName = itItem->first;

			// 項目の参照
			Item& item = itItem->second;


			// int32_t型の値
			if (std::holds_alternative<int32_t>(item))
			{
				int32_t* ptr = std::get_if<int32_t>(&item);
				ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
			}
			else if(std::holds_alternative<float>(item))
			{
				float* ptr = std::get_if<float>(&item);
				ImGui::SliderFloat(itemName.c_str(), ptr, 0.0f, 100.0f);
			}
			else if (std::holds_alternative<Vector2>(item))
			{

			}
		}


		ImGui::EndMenu();
	}


	ImGui::EndMenuBar();
	ImGui::End();
	*/

#endif
}

/// <summary>
/// 終了処理
/// </summary>
void RecordSetting::Finalize()
{
	delete instance_;
}

/// <summary>
/// グループの作成
/// </summary>
/// <param name="groupName">グループ名</param>
void RecordSetting::CreateGroup(const std::string& groupName)
{
	// 指定のオブジェクトがなければ追加
	datas_[groupName];
}