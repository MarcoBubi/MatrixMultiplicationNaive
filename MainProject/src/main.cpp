#include <iostream>
#include <chrono>
#include "Matrix.h"

int main()
{
	Matrix first(4096);
	Matrix second(4096);
	first.RandomizeMatrixValues(-10, 10);
	second.RandomizeMatrixValues(-10, 10);

	auto startTimer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	/*Multiplication!*/
	Matrix product = first * second;

	auto endTimer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	auto elapsedTime = endTimer - startTimer;
	std::cout << "Operation took " << elapsedTime.count() << " ms." << std::endl;
}
