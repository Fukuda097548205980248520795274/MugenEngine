#pragma once
#include <Windows.h>
#include <dxcapi.h>
#include <cassert>
#include <wrl.h>

#include "../../../LogFile/LogFile.h"
#include "../../../Func/ConvertString/ConvertString.h"

class DirectXShaderCompile
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logfile"></param>
	void Initialize(LogFile* logfile);

	/// <summary>
	/// シェーダをコンパイルする
	/// </summary>
	/// <param name="filePath"></param>
	/// <param name="profile"></param>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<IDxcBlob> CompilerShader(const std::wstring& filePath, const wchar_t* profile);



private:

	// ログファイル
	LogFile* logFile_ = nullptr;


	// DXCユーティリティ
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils_ = nullptr;

	// DXCコンパイラ
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler_ = nullptr;

	// DXCインクルードハンドラ
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler_ = nullptr;
};

