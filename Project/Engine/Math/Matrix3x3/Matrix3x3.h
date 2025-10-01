#pragma once
#include <cmath>
#include <cstdint>
#include <cassert>
#include "../Vector2/Vector2.h"
#include "../Vector3/Vector3.h"

// 3x3行列
struct Matrix3x3
{
	float m[3][3];

	// 加算
	Matrix3x3 operator+=(const Matrix3x3& matrix)
	{
		for (int32_t i = 0; i < 3; ++i)
		{
			for (int32_t j = 0; j < 3; ++j)
			{
				this->m[i][j] += matrix.m[i][j];
			}
		}

		return *this;
	}

	// 減算
	Matrix3x3 operator-=(const Matrix3x3& matrix)
	{
		for (int32_t i = 0; i < 3; ++i)
		{
			for (int32_t j = 0; j < 3; ++j)
			{
				this->m[i][j] -= matrix.m[i][j];
			}
		}

		return *this;
	}

	// スカラー倍
	Matrix3x3 operator*=(float scalar)
	{
		for (uint32_t i = 0; i < 3; ++i)
		{
			for (uint32_t j = 0; j < 3; ++j)
			{
				this->m[i][j] *= scalar;
			}
		}

		return *this;
	}

	// 乗算
	Matrix3x3 operator*=(const Matrix3x3& matrix)
	{
		// 積
		Matrix3x3 multiply;

		multiply.m[0][0] = this->m[0][0] * matrix.m[0][0] + this->m[0][1] * matrix.m[1][0] + this->m[0][2] * matrix.m[2][0];
		multiply.m[0][1] = this->m[0][0] * matrix.m[0][1] + this->m[0][1] * matrix.m[1][1] + this->m[0][2] * matrix.m[2][1];
		multiply.m[0][2] = this->m[0][0] * matrix.m[0][2] + this->m[0][1] * matrix.m[1][2] + this->m[0][2] * matrix.m[2][2];

		multiply.m[1][0] = this->m[1][0] * matrix.m[0][0] + this->m[1][1] * matrix.m[1][0] + this->m[1][2] * matrix.m[2][0];
		multiply.m[1][1] = this->m[1][0] * matrix.m[0][1] + this->m[1][1] * matrix.m[1][1] + this->m[1][2] * matrix.m[2][1];
		multiply.m[1][2] = this->m[1][0] * matrix.m[0][2] + this->m[1][1] * matrix.m[1][2] + this->m[1][2] * matrix.m[2][2];

		multiply.m[2][0] = this->m[2][0] * matrix.m[0][0] + this->m[2][1] * matrix.m[1][0] + this->m[2][2] * matrix.m[2][0];
		multiply.m[2][1] = this->m[2][0] * matrix.m[0][1] + this->m[2][1] * matrix.m[1][1] + this->m[2][2] * matrix.m[2][1];
		multiply.m[2][2] = this->m[2][0] * matrix.m[0][2] + this->m[2][1] * matrix.m[1][2] + this->m[2][2] * matrix.m[2][2];

		*this = multiply;

		return *this;
	}
};


namespace
{
	// 加算
	Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2)
	{
		// 加算
		Matrix3x3 add;

		for (int32_t i = 0; i < 3; ++i)
		{
			for (int32_t j = 0; j < 3; ++j)
			{
				add.m[i][j] = m1.m[i][j] + m2.m[i][j];
			}
		}

		return add;
	}

	// 減算
	Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2)
	{
		// 加算
		Matrix3x3 subtract;

		for (int32_t i = 0; i < 3; ++i)
		{
			for (int32_t j = 0; j < 3; ++j)
			{
				subtract.m[i][j] = m1.m[i][j] - m2.m[i][j];
			}
		}

		return subtract;
	}

	// スカラー倍
	Matrix3x3 operator*(float scalar, const Matrix3x3& matrix)
	{
		// スカラー倍
		Matrix3x3 scalarMultiply;

		for (uint32_t i = 0; i < 3; ++i)
		{
			for (uint32_t j = 0; j < 3; ++j)
			{
				scalarMultiply.m[i][j] = scalar * matrix.m[i][j];
			}
		}

		return scalarMultiply;
	}

	// スカラー倍
	Matrix3x3 operator*(const Matrix3x3& matrix, float scalar)
	{
		// スカラー倍
		Matrix3x3 scalarMultiply;

		for (uint32_t i = 0; i < 3; ++i)
		{
			for (uint32_t j = 0; j < 3; ++j)
			{
				scalarMultiply.m[i][j] = matrix.m[i][j] * scalar;
			}
		}

		return scalarMultiply;
	}

	// 乗算
	Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2)
	{
		// 積
		Matrix3x3 multiply;

		multiply.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0];
		multiply.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1];
		multiply.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2];

		multiply.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0];
		multiply.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1];
		multiply.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2];

		multiply.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0];
		multiply.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1];
		multiply.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2];

		return multiply;
	}
}


/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 Transform(const Vector2& vector, const Matrix3x3& matrix);

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix3x3& matrix);

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 TransformNormal(const Vector2& vector, const Matrix3x3& matrix);

/// <summary>
/// 単位行列を作成する
/// </summary>
/// <returns></returns>
Matrix3x3 MakeIdentityMatrix3x3();

/// <summary>
/// 転置行列を作成する
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix3x3 MakeTransposeMatrix3x3(const Matrix3x3& matrix);

/// <summary>
/// 拡大縮小行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix3x3 Make2DScaleMatrix3x3(const Vector2& scale);

/// <summary>
/// 回転行列を作成する
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix3x3 Make2DRotateMatrix3x3(float radian);

/// <summary>
/// 平行移動行列を作成する
/// </summary>
/// <param name="translation"></param>
/// <returns></returns>
Matrix3x3 Make2DTranslateMatrix3x3(const Vector2& translation);

/// <summary>
/// アフィン変換行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <param name="radian"></param>
/// <param name="translation"></param>
/// <returns></returns>
Matrix3x3 Make2DAffineMatrix3x3(const Vector2& scale, float radian, const Vector2& translation);

/// <summary>
/// 逆行列を作成する
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix3x3 MakeInverseMatrix3x3(const Matrix3x3& m);

/// <summary>
/// 平行投影行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <returns></returns>
Matrix3x3 MakeOrthographicMatrix3x3(float left, float top, float right, float bottom);

/// <summary>
/// ビューポート変換行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
Matrix3x3 MakeViewportMatrix3x3(float left, float top, float width, float height);