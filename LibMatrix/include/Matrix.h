#pragma once
#include <iostream>
#include <vector>

class Matrix
{
public:
	Matrix();
	explicit Matrix(const uint32_t size, const double value = 0.0);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;
	~Matrix();

	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other) noexcept;
	Matrix operator*(const Matrix& rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
	bool operator==(const Matrix& other);

	const uint32_t GetSize();
	const double GetValue(const uint32_t x, const uint32_t y);
	void SetValue(const uint32_t x, const uint32_t y, const double value);
	void RandomizeMatrixValues(const double minValue, const double maxValue);

private:
	void AllocateMemory();
	void DealocateMemory();

	static constexpr uint32_t MIN_MATRIX_N = 4096;

	uint32_t _row = MIN_MATRIX_N;
	uint32_t _col = MIN_MATRIX_N;
	double** _data;
};

std::ostream& operator<<(std::ostream& os, const Matrix& mat);
