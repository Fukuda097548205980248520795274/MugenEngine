#include "RecordSetting.h"

// インスタンス
std::unique_ptr<RecordSetting> RecordSetting::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
RecordSetting* RecordSetting::GetInstance()
{
	// nullなら生成する
	if (instance_ == nullptr)
	{
		instance_ = std::make_unique<RecordSetting>();
	}

	return instance_.get();
}

/// <summary>
/// 更新処理
/// </summary>
void RecordSetting::Update()
{
	// メニューバーを使用する
	if (!ImGui::Begin("Setting"))
	{
		ImGui::End();
		return;
	}



	// 各グループについて
	for (Datas::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup)
	{
		// グループ名を取得
		const std::string& groupName = itGroup->first;

		// グループ参照
		Group& group = itGroup->second;

		// 開いていないときは処理しない
		if (!ImGui::TreeNode(groupName.c_str()))continue;


		// 各項目について
		for (Group::iterator itItem = group.begin(); itItem != group.end(); ++itItem)
		{
			// 項目名を取得
			const std::string& itemName = itItem->first;

			// 項目参照
			Item& item = itItem->second;


			// bool型
			if (std::holds_alternative<bool*>(item))
			{
				bool** ptr = std::get_if<bool*>(&item);
				ImGui::Checkbox(itemName.c_str(), *ptr);
			}
			else if(std::holds_alternative<int32_t*>(item))
			{
				// int32_t型
				int32_t** ptr = std::get_if<int32_t*>(&item);
				ImGui::SliderInt(itemName.c_str(), *ptr, -50, 50);
			}
			else if (std::holds_alternative<float*>(item))
			{
				// float型
				float** ptr = std::get_if<float*>(&item);
				ImGui::SliderFloat(itemName.c_str(), *ptr, -50.0f, 50.0f);
			}
			else if (std::holds_alternative<Vector2*>(item))
			{
				// Vector2型
				Vector2** ptr = std::get_if<Vector2*>(&item);
				ImGui::SliderFloat2(itemName.c_str(), reinterpret_cast<float*>(*ptr), -50.0f, 50.0f);
			}
			else if (std::holds_alternative<Vector3*>(item))
			{
				// Vector3型
				Vector3** ptr = std::get_if<Vector3*>(&item);
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(*ptr), -50.0f, 50.0f);
			}
			else if (std::holds_alternative<Vector4*>(item))
			{
				// Vector4型
				Vector4** ptr = std::get_if<Vector4*>(&item);
				ImGui::SliderFloat4(itemName.c_str(), reinterpret_cast<float*>(*ptr), -50.0f, 50.0f);
			}
		}


		ImGui::Text("\n");

		// 保存ボタン
		if (ImGui::Button("Save"))
		{
			SaveFile(groupName);
			std::string message = std::format("{} : saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "RecordSetting", 0);
		}

		ImGui::Text("\n");

		// ロードボタン
		if (ImGui::Button("Load"))
		{
			RegistGroupDataReflection(groupName);
			std::string message = std::format("{} : loaded.", groupName);
			MessageBoxA(nullptr, message.c_str(), "RecordSetting", 0);
		}


		// 終了
		ImGui::TreePop();
	}



	// 終了
	ImGui::End();
}

/// <summary>
/// 終了処理
/// </summary>
void RecordSetting::Finalize()
{
	instance_.reset();
	instance_ = nullptr;
}

/// <summary>
/// 新規ファイルを作成する
/// </summary>
/// <param name="groupName"></param>
void RecordSetting::CreateRecordFile(const std::string& groupName)
{
	// ディレクトリがなければ作成する
	std::filesystem::path dir(kDirectory);
	if (!std::filesystem::exists(dir))
	{
		std::filesystem::create_directory(dir);
	}

	// ファイルパス
	std::string filePath = kDirectory + groupName + ".json";

	// 入力ファイルストリーム
	std::ifstream ifs;
	ifs.open(filePath);

	// 既存のファイルを削除する
	if (ifs.is_open())
	{
		ifs.close();
		std::filesystem::remove(filePath);
	}

	// 新たにファイルを作成する
	std::ofstream ofs;
	ofs.open(filePath);
}

/// <summary>
/// ファイルを記録する
/// </summary>
/// <param name="groupName"></param>
void RecordSetting::SaveFile(const std::string& groupName)
{
	// グループを検索
	Datas::iterator itGroup = datas_.find(groupName);

	// 未登録のときは処理しない
	if (itGroup == datas_.end())
		return;


	// データコンテナ
	json root;
	root = json::object();

	// jsonオブジェクトに登録
	root[groupName] = json::object();

	// 各行もについて
	for (Group::iterator itItem = itGroup->second.begin(); itItem != itGroup->second.end(); ++itItem)
	{
		// 項目名を取得
		const std::string& itemName = itItem->first;

		// 項目を参照
		Item& item = itItem->second;


		// bool型
		if (std::holds_alternative<bool*>(item))
		{
			bool* value = std::get<bool*>(item);
			root[groupName][itemName] = *value;
		}
		else if (std::holds_alternative<int32_t*>(item))
		{
			// int32_t型
			int32_t* value = std::get<int32_t*>(item);
			root[groupName][itemName] = *value;
		}
		else if (std::holds_alternative<float*>(item))
		{
			//float型
			float* value = std::get<float*>(item);
			root[groupName][itemName] = *value;
		}
		else if (std::holds_alternative<Vector2*>(item))
		{
			// Vector2型
			Vector2* value = std::get<Vector2*>(item);
			root[groupName][itemName] = json::array({ value->x , value->y });
		}
		else if (std::holds_alternative<Vector3*>(item))
		{
			// Vector3型
			Vector3* value = std::get<Vector3*>(item);
			root[groupName][itemName] = json::array({ value->x , value->y , value->z });
		}
		else if (std::holds_alternative<Vector4*>(item))
		{
			// Vector4型
			Vector4* value = std::get<Vector4*>(item);
			root[groupName][itemName] = json::array({ value->x, value->y, value->z , value->w });
		}
	}

	// ディレクトリがなければ作成する
	std::filesystem::path dir(kDirectory);
	if (!std::filesystem::exists(dir))
	{
		std::filesystem::create_directory(dir);
	}

	// 新規ファイルを作成する
	CreateRecordFile(groupName);

	// ファイルパス
	std::string filePath = kDirectory + groupName + ".json";

	// 出力ファイルストリーム
	std::ofstream ofs;
	ofs.open(filePath);

	// ファイルが開けなかった時
	if (ofs.is_open() == false)
	{
		return;
	}

	// ファイルにJSON文字列を書き込む
	ofs << std::setw(4) << root << std::endl;

	// ファイルを閉じる
	ofs.close();

	return;
}

/// <summary>
/// 登録した調整項目の値に、ファイルの値を反映させる
/// </summary>
/// <param name="groupName"></param>
void RecordSetting::RegistGroupDataReflection(const std::string& groupName)
{
	// ファイルパス
	std::string filePath = kDirectory + groupName + ".json";

	// 入力ファイルストリーム
	std::ifstream ifs;
	ifs.open(filePath);

	// ファイルが開けなかったら何もしない
	if (!ifs.is_open())
		return;


	// データコンテナ
	json root;
	ifs >> root;

	// ファイルを閉じる
	ifs.close();

	// グループを検索
	json::iterator itGroup = root.find(groupName);

	// 未登録は何もしない
	if (itGroup == root.end())
		return;


	// グループ参照
	Group& group = datas_[groupName];

	// json各項目について
	for (json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem)
	{
		// アイテム名を取得
		const std::string& itemName = itItem.key();

		// データの各項目について
		for (Group::iterator itDataItem = group.begin(); itDataItem != group.end(); ++itDataItem)
		{
			// アイテム名を取得
			const std::string& dataItemName = itDataItem->first;

			// 一致したら処理する
			if (strcmp(itemName.c_str(), dataItemName.c_str()))
				continue;

			// アイテムを参照
			Item& item = itDataItem->second;


			// bool型
			if (itItem->is_boolean() && std::holds_alternative<bool*>(item))
			{
				bool value = itItem->get<bool>();
				bool** ptr = std::get_if<bool*>(&item);
				**ptr = value;
			}
			else if (itItem->is_number_integer() && std::holds_alternative<int32_t*>(item))
			{
				// int32_t型
				int32_t value = itItem->get<int32_t>();
				int32_t** ptr = std::get_if<int32_t*>(&item);
				**ptr = value;
			}
			else if (itItem->is_number_float() && std::holds_alternative<float*>(item))
			{
				// float型
				float value = itItem->get<float>();
				float** ptr = std::get_if<float*>(&item);
				**ptr = value;
			}
			else if (itItem->is_array() && itItem->size() == 2 && std::holds_alternative<Vector2*>(item))
			{
				// Vector2型
				Vector2 value = { itItem->at(0), itItem->at(1) };
				Vector2** ptr = std::get_if<Vector2*>(&item);
				**ptr = value;
			}
			else if (itItem->is_array() && itItem->size() == 3 && std::holds_alternative<Vector3*>(item))
			{
				// Vector3型
				Vector3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
				Vector3** ptr = std::get_if<Vector3*>(&item);
				**ptr = value;
			}
			else if (itItem->is_array() && itItem->size() == 4 && std::holds_alternative<Vector4*>(item))
			{
				// Vector4型
				Vector4 value = { itItem->at(0), itItem->at(1), itItem->at(2), itItem->at(3) };
				Vector4** ptr = std::get_if<Vector4*>(&item);
				**ptr = value;
			}


			break;
		}
	}
}