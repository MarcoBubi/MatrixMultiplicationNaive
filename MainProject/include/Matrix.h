#pragma once
#include <vector>

class Matrix
{
public:
	Matrix();
	Matrix(const uint32_t size, double value = 0.0);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);

	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	Matrix operator*(const Matrix& rhs) const;

	~Matrix();

	void SetValue(const uint32_t x, const uint32_t y, const double value);
	void RandomizeMatrixValues(const double minValue, const double maxValue);
	void PrintMatrix();

private:
	void AllocateMemory();
	void DealocateMemory();

	static constexpr uint32_t MIN_MATRIX_N = 4096;

	uint32_t _row = MIN_MATRIX_N;
	uint32_t _col = MIN_MATRIX_N;
	double** _data;
};
