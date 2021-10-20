#include "pch.h"
#include "Matrix.h"

TEST(MatrixTest, BasicMultiplication)
{
	Matrix firstM(2);
	Matrix secondM(2);

	firstM.SetValue(0, 0, 0);
	firstM.SetValue(0, 1, 1);
	firstM.SetValue(1, 0, 2);
	firstM.SetValue(1, 1, 3);

	secondM.SetValue(0, 0, 1);
	secondM.SetValue(0, 1, 2);
	secondM.SetValue(1, 0, 3);
	secondM.SetValue(1, 1, 4);

	Matrix thirdM = firstM * secondM;

	// precalculated values where 0,0 = 3
	EXPECT_EQ(thirdM.GetValue(0,0), 3);
	EXPECT_EQ(thirdM.GetValue(0,1), 4);
	EXPECT_EQ(thirdM.GetValue(1,0), 11);
	EXPECT_EQ(thirdM.GetValue(1,1), 16);
}

TEST(MatrixTest, MatrixInitialisationWithValue)
{
	Matrix firstM(2, 1);

	EXPECT_EQ(firstM.GetValue(0, 0), 1);
	EXPECT_EQ(firstM.GetValue(0, 1), 1);
	EXPECT_EQ(firstM.GetValue(1, 0), 1);
	EXPECT_EQ(firstM.GetValue(1, 1), 1);
}

TEST(MatrixTest, RandomizedValuesInBounds)
{
	Matrix firstM(2);
	firstM.RandomizeMatrixValues(5, 10);

	EXPECT_GE(firstM.GetValue(0, 0), 5);
	EXPECT_LE(firstM.GetValue(0, 0), 10);
}

TEST(MatrixTest, MatrixSizesTest)
{
	Matrix firstM;
	Matrix secondM(3);
	Matrix thirdM(500, 1);

	EXPECT_TRUE(firstM.GetSize() == 4096);
	EXPECT_TRUE(secondM.GetSize() == 3);
	EXPECT_TRUE(thirdM.GetSize() == 500);
}

TEST(MatrixTest, MatrixOutputToConsole)
{
	Matrix firstM(3);
	firstM.SetValue(0, 0, 9);

	testing::internal::CaptureStdout();
	std::cout << firstM;
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_TRUE(output.at(0) == '9');
}

TEST(MatrixTest, MatrixEqualityTest)
{
	Matrix firstM(3);
	Matrix secondM = firstM;

	EXPECT_TRUE(secondM == firstM);

	secondM.SetValue(0, 0, 5);

	EXPECT_FALSE(secondM == firstM);

	Matrix thirdM(4);

	EXPECT_FALSE(thirdM == firstM);
}

TEST(MatrixTestAssert, DifferentMatrixesMultiplicationAssert)
{
	Matrix firstM(3);
	Matrix secondM(4);

	ASSERT_DEATH(firstM * secondM, "");
}

TEST(MatrixTestAssert, GetValueOutOfRangeAssert)
{
	Matrix firstM(3);

	ASSERT_DEATH(firstM.GetValue(4,4), "");
}

TEST(MatrixConstructorTest, EmptyConstructorTest)
{
	Matrix firstM;

	EXPECT_TRUE(firstM.GetSize() == 4096);
}

TEST(MatrixConstructorTest, ParameterConstructorTest)
{
	Matrix firstM(2);
	Matrix secondM(2, 2);

	EXPECT_TRUE(firstM.GetSize() == 2);
	EXPECT_EQ(firstM.GetValue(0, 0), 0);
	EXPECT_EQ(secondM.GetValue(0, 0), 2);
}

TEST(MatrixConstructorTest, CopyConstructorTest)
{
	Matrix firstM(2);
	firstM.RandomizeMatrixValues(0, 3);
	Matrix secondM(firstM);

	EXPECT_EQ(firstM.GetValue(0, 0), secondM.GetValue(0, 0));
	EXPECT_EQ(firstM.GetValue(0, 1), secondM.GetValue(0, 1));
	EXPECT_EQ(firstM.GetValue(1, 0), secondM.GetValue(1, 0));
	EXPECT_EQ(firstM.GetValue(1, 1), secondM.GetValue(1, 1));
}

TEST(MatrixConstructorTest, MoveConstructorTest)
{
	Matrix firstM(2);
	firstM.RandomizeMatrixValues(1, 3);
	Matrix secondM(std::move(firstM));

	ASSERT_DEATH(firstM.GetValue(0,0), "");
	EXPECT_GE(secondM.GetValue(1, 0), 1);
	EXPECT_LE(secondM.GetValue(1, 1), 3);
}

TEST(MatrixAssignmentTest, CopyAssignmentTest)
{
	Matrix firstM(2);
	Matrix secondM(5);

	firstM.RandomizeMatrixValues(1, 3);
	firstM = secondM;

	EXPECT_TRUE(firstM.GetSize() == secondM.GetSize());
	EXPECT_EQ(firstM.GetValue(0,0), secondM.GetValue(0,0));
}

TEST(MatrixAssignmentTest, MoveAssignmentTest)
{
	Matrix firstM;

	EXPECT_EQ(firstM.GetSize(), 4096);

	firstM = std::move(Matrix(2));

	EXPECT_EQ(firstM.GetSize(), 2);
}
