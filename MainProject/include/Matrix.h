#pragma once
#include <vector>

#define MIN_MATRIX_N 4096

class Matrix
{
public:
	Matrix();
	Matrix(uint32_t size, double value = 0);
	Matrix(const Matrix& obj);

	void AddValue(uint32_t x, uint32_t y, double value);
	void RandomizeMatrixValues(double minValue, double maxValue);
	void PrintMatrix();

	uint32_t GetRowSize() const;
	uint32_t GetColSize() const;
	Matrix operator*(const Matrix& rhs) const;

	uint32_t _row = MIN_MATRIX_N;
	uint32_t _col = MIN_MATRIX_N;
	std::vector< std::vector<double> > _data;
};
