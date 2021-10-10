#include <iostream>
#include <chrono>
#include "Matrix.h"

int main()
{
	Matrix matrixA(4096);
	Matrix matrixB(4096);
	matrixA.RandomizeMatrixValues(-10, 10);
	matrixB.RandomizeMatrixValues(-10, 10);

	auto startTimer = std::chrono::high_resolution_clock::now();
	Matrix productMatrixAB = matrixA * matrixB;
	auto endTimer = std::chrono::high_resolution_clock::now();

	auto executionTime = std::chrono::duration_cast<std::chrono::seconds>(startTimer - endTimer);
	std::cout << "Operation took " << executionTime.count() << " ms." << std::endl;
}
