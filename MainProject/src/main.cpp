#include <iostream>
#include <ctime>
#include "Matrix.h"

int main()
{
	Matrix first(1000);
	Matrix second(1000);
	first.RandomizeMatrixValues(-10, 10);
	second.RandomizeMatrixValues(-10, 10);

	clock_t tStart = clock(); // time measurement
	Matrix product = first * second;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
