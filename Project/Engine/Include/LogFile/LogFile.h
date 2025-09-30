#pragma once
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>
#include <string>

class LogFile
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ログを出力する
	/// </summary>
	/// <param name="message"></param>
	void Log(const std::string& message);


private:

	/// <summary>
	/// ログストリームを生成する
	/// </summary>
	/// <returns></returns>
	std::ofstream CreateLogStream();

	/// <summary>
	/// ログストリーム
	/// </summary>
	std::ofstream logStream_;
};

