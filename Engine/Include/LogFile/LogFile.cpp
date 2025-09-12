#include "LogFile.h"

/// <summary>
/// 初期化
/// </summary>
void LogFile::Initialize()
{
	// ログストリームを生成する
	logStream_ = CreateLogStream();
}

/// <summary>
/// ログを出力する
/// </summary>
/// <param name="message"></param>
void LogFile::Log(const std::string& message)
{
	logStream_ << message << std::endl;
	OutputDebugStringA(message.c_str());
}

/// <summary>
/// ログストリームを生成する
/// </summary>
/// <returns></returns>
std::ofstream LogFile::CreateLogStream()
{
	// ディレクトリを掘る
	CreateDirectory(L"./Engine/Output/Logs", nullptr);

	// 現在時刻（UTC時刻）を取得
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// ログファイルをコンマを使わず秒にする
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> nowSeconds =
		std::chrono::time_point_cast<std::chrono::seconds>(now);

	// 日本時間（PCの設定時間）に変換
	std::chrono::zoned_time localTime{ std::chrono::current_zone(), nowSeconds };

	// formatを使って年月日_時分秒の文字列に変換
	std::string dateString = std::format("{:%Y%m%d_%H%M%S}", localTime);

	// ファイル名は時刻を使う
	std::string logFilePath = std::string("./Engine/Output/Logs/") + dateString + ".log";

	// ファイルを作って書き込み準備
	std::ofstream logStream(logFilePath);
	return logStream;
}