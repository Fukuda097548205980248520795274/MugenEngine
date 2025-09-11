#pragma once
#include <Windows.h>
#include <string>
#include <format>

/// <summary>
/// string -> wstring
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
std::wstring ConvertString(const std::string& str);

/// <summary>
/// wstring -> string
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
std::string ConvertString(const std::wstring& str);

/// <summary>
/// ログを出力する
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
void Log(const std::string& message);