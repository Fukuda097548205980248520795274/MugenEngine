#include "Probability.h"

/// <summary>
/// 階乗を行う
/// </summary>
/// <param name="num">数値</param>
/// <returns></returns>
uint32_t Factorial(uint32_t num)
{
	if (num > 0)
	{
		return num * Factorial(num - 1);
	}

	return 1;
}

/// <summary>
/// 順列を行う
/// </summary>
/// <param name="resultNum">全体の数</param>
/// <param name="takeOutNum">取り出して並べる数</param>
/// <returns></returns>
uint32_t Permutation(uint32_t resultNum, uint32_t takeOutNum)
{
	return Factorial(resultNum) / Factorial(resultNum - takeOutNum);
}

/// <summary>
/// 組み合わせを行う
/// </summary>
/// <param name="resultNum">全体の数</param>
/// <param name="takeOutNum">取り出して並べる数</param>
/// <returns></returns>
uint32_t Combination(uint32_t resultNum, uint32_t takeOutNum)
{
	return Permutation(resultNum, takeOutNum) / Factorial(takeOutNum);
}