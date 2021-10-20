#include "pch.h"

#include "Matrix.h"
#include <cassert>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

Matrix::Matrix()
{
	AllocateMemory();
}

Matrix::Matrix(const uint32_t size, const double value /* = 0.0 */)
	: _row{ size }
	, _col{ size }
{
	AllocateMemory();
	for (unsigned int i = 0; i < _row; ++i)
	{
		for (unsigned int j = 0; j < _col; ++j)
		{
			_data[i][j] = value;
		}
	}
}

Matrix::Matrix(const Matrix& other)
	: _row{ other._row }
	, _col{ other._col }
{
	AllocateMemory();

	for (unsigned int i = 0; i < _row; ++i)
	{
		for (unsigned int j = 0; j < _col; ++j)
		{
			_data[i][j] = other._data[i][j];
		}
	}
}

Matrix::Matrix(Matrix&& other) noexcept
	: _row{ other._row }
	, _col{ other._col }
	, _data{ other._data }
{
	other._row = MIN_MATRIX_N;
	other._col = MIN_MATRIX_N;
	other._data = nullptr;
}

Matrix::~Matrix()
{
	DealocateMemory();
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if(this == &other)
	{
		return *this;
	}
	DealocateMemory();
	_row = other._row;
	_col = other._col;
	AllocateMemory();

	for (unsigned int i = 0; i < _row; ++i)
	{
		for (unsigned int j = 0; j < _col; ++j)
		{
			_data[i][j] = other._data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	DealocateMemory();
	_row = other._row;
	_col = other._col;

	AllocateMemory();
	_data = other._data;

	other._row = MIN_MATRIX_N;
	other._col = MIN_MATRIX_N;
	other._data = nullptr;

	return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	assert(_col == rhs._row);

	Matrix product(_col);
	uint32_t rhsColSize = rhs._col;

	for (uint32_t i = 0; i < _row; ++i)
	{
		for (uint32_t j = 0; j < rhsColSize; ++j)
		{
			product._data[i][j] = 0;
			for (uint32_t k = 0; k < _col; ++k)
			{
				product._data[i][j] += _data[i][k] * rhs._data[k][j];
			}
		}
	}

	return product;
}

bool Matrix::operator==(const Matrix& other)
{
	if (_col != other._col)
	{
		return false;
	}

	for (uint32_t i = 0; i < _row; ++i)
	{
		for (uint32_t j = 0; j < _col; ++j)
		{
			if (_data[i][j] != other._data[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

const uint32_t Matrix::GetSize()
{
	return _col;
}

const double Matrix::GetValue(const uint32_t x, const uint32_t y)
{
	assert(x < _col || y < _row);

	return _data[x][y];
}

void Matrix::SetValue(const uint32_t x, const uint32_t y, const double value)
{
	assert(x < _col || y < _row);

	_data[x][y] = value;
}

void Matrix::RandomizeMatrixValues(const double minValue, const double maxValue)
{
	std::random_device rd; // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(minValue, maxValue);

	for (uint32_t i = 0; i < _row; ++i)
	{
		for (uint32_t j = 0; j < _col; ++j)
		{
			_data[i][j] = dis(gen);
		}
	}
}

void Matrix::AllocateMemory()
{
	_data = new double*[_row];
	for (unsigned int i = 0; i < _row; ++i)
	{
		_data[i] = new double[_col];
	}
}

void Matrix::DealocateMemory()
{
	if (_data == nullptr)
	{
		return;
	}

	for (unsigned int i = 0; i < _row; ++i)
	{
		delete[] _data[i];
	}
	delete[] _data;
	_data = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	for (uint32_t i = 0; i < mat._row; ++i)
	{
		for (uint32_t j = 0; j < mat._col; ++j)
		{
			os << mat._data[i][j] << '\t';
		}

		os << '\n';
	}

	return os;
}
