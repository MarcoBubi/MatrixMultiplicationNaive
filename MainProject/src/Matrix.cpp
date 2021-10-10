#pragma once
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

#define MIN_MATRIX_N 4096

Matrix::Matrix()
:	_data{ _row, std::vector<double>(_col, 0) }
{
}

Matrix::Matrix(uint32_t size, double value /* = 0 */)
:	_row{ size },
	_col{ size },
	_data{ _row, std::vector<double>(_col, value) }
{
}

Matrix::Matrix(const Matrix& obj)
:	_row{ obj._row },
	_col{ obj._col },
	_data{ obj._data }
{
}

void Matrix::AddValue(uint32_t x, uint32_t y, double value)
{
	if(x > _col || y > _row)
	{
		throw ("Target index out of bound!");
	}

	_data[x][y] = value;
}

void Matrix::RandomizeMatrixValues(double minValue, double maxValue)
{
	srand(time(nullptr)); // for this purpose it will work

	for (uint32_t i = 0; i < _row; ++i)
	{
		for (uint32_t j = 0; j < _col; ++j)
		{
			_data[i][j] = minValue + ((double)rand() / RAND_MAX) * (maxValue - minValue);
		}
	}
}

void Matrix::PrintMatrix()
{
	for (uint32_t i = 0; i < _row; ++i)
	{
		for (uint32_t j = 0; j < _col; ++j)
		{
			std::cout << _data[i][j] << " ";
		}

		std::cout << "\n";
	}
}

uint32_t Matrix::GetRowSize() const
{
	return _row;
}

uint32_t Matrix::GetColSize() const
{
	return _col;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	if (_col != rhs.GetRowSize())
	{
		throw "Both matrices should be square matrices!";
	}

	Matrix product(_col);
	uint32_t rhsColSize = rhs.GetColSize();

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