#include "MatrixTestSuite.h"
#include "Matrix.h"
#include "Direction.h"
#include "Point.h"
#include "cute.h"

#include <array>



void testDefaultMatrixIsAllZero() {
	constexpr auto kRows = 4;
	constexpr auto kColumns = 4;
	Matrix<kRows, kColumns> const m{};

	for (auto const row : Range<Row>{0_row, Row{kRows}}) {
		for (auto const column : Range<Column>{0_column, Column{kColumns}}) {
			double const value = m[row, column];
			ASSERT_EQUAL(0.0, value);
		}
	}
}

void testMatrixConstructedWithValues() {
	auto const kRows = 4;
	auto const kColumns = 4;
	Matrix<kRows, kColumns> const m {
					 1.0,  2.0,  3.0,  4.0,
					 5.5,  6.5,  7.5,  8.5,
					 9.0, 10.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5
	};

	std::array<double, 16> const expectedValues {
					 1.0,  2.0,  3.0,  4.0,
					 5.5,  6.5,  7.5,  8.5,
					 9.0, 10.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5
	};
	std::array<double, 16> const actualValues {
		m[0_row, 0_column], m[0_row, 1_column], m[0_row, 2_column], m[0_row, 3_column],
		m[1_row, 0_column], m[1_row, 1_column],	m[1_row, 2_column],	m[1_row, 3_column],
		m[2_row, 0_column],	m[2_row, 1_column],	m[2_row, 2_column],	m[2_row, 3_column],
		m[3_row, 0_column],	m[3_row, 1_column],	m[3_row, 2_column],	m[3_row, 3_column]
	};

	ASSERT_EQUAL(expectedValues, actualValues);
}

void testTwoTimesTwoMatrix() {
	auto const kRows = 2;
	auto const kColumns = 2;
	Matrix<kRows, kColumns> const m {
		-3.0,  5.0,
		 1.0, -2.0
	};
	std::array<double, 4> const expectedValues {
		-3.0,  5.0,
		 1.0, -2.0
	};
	std::array<double, 4> const actualValues {
		m[0_row, 0_column], m[0_row, 1_column],
		m[1_row, 0_column], m[1_row, 1_column]
	};
	ASSERT_EQUAL(expectedValues, actualValues);
}


void testThreeTimesThreeMatrix() {
	auto const kRows = 3;
	auto const kColumns = 3;
	Matrix<kRows, kColumns> const m {
		-3.0,  5.0,  0.0,
		 1.0, -2.0, -7.0,
		 0.0,  1.0,  1.0
	};
	std::array<double, 9> const expectedValues {
		-3.0,  5.0,  0.0,
		 1.0, -2.0, -7.0,
		 0.0,  1.0,  1.0
	};
	std::array<double, 9> const actualValues {
		m[0_row, 0_column], m[0_row, 1_column], m[0_row, 2_column],
		m[1_row, 0_column], m[1_row, 1_column], m[1_row, 2_column],
		m[2_row, 0_column], m[2_row, 1_column], m[2_row, 2_column]
	};
	ASSERT_EQUAL(expectedValues, actualValues);
}

void testMultiplyTwoMatrices() {
	auto const kRows = 4;
	auto const kColumns = 4;
	Matrix<kRows, kColumns> const m1 {
		 1.0,  2.0,  3.0,  4.0,
		 2.0,  3.0,  4.0,  5.0,
		 3.0,  4.0,  5.0,  6.0,
		 4.0,  5.0,  6.0,  7.0
	};
	Matrix<kRows, kColumns> const m2 {
		 0.0,  1.0,  2.0,  4.0,
		 1.0,  2.0,  4.0,  8.0,
		 2.0,  4.0,  8.0, 16.0,
		 4.0,  8.0, 16.0, 32.0
	};
	Matrix<kRows, kColumns> const expected {
		24.0,  49.0,  98.0, 196.0,
		31.0,  64.0, 128.0, 256.0,
		38.0,  79.0, 158.0, 316.0,
		45.0,  94.0, 188.0, 376.0
	};

	ASSERT_EQUAL(expected, m1 * m2);
}

void testAsMatrix() {
	Direction const direction{1.0, 2.0, 3.0};
	Matrix<4, 1> const expected{1.0, 2.0, 3.0, 0.0};
	ASSERT_EQUAL(expected, asMatrix(direction));
}

void testMultiplyMatrixAndDirection() {
	Matrix<4, 4> const A {
		1.0, 2.0, 3.0, 4.0,
		2.0, 4.0, 4.0, 2.0,
		8.0, 6.0, 4.0, 1.0,
		0.0, 0.0, 0.0, 1.0
	};
	Direction const direction{1.0, 2.0, 3.0};
	Matrix<4, 1> const expected{14.0, 22.0, 32.0, 0.0};
	auto const result = A * asMatrix(direction);
	ASSERT_EQUAL(expected, result);
}

void testMultiplyMatrixAndPoint() {
	Matrix<4, 4> const A {
		1.0,  0.0,  0.0,  5.0,
		0.0,  1.0,  0.0, -3.0,
		0.0,  0.0,  1.0,  2.0,
		0.0,  0.0,  0.0,  1.0
	};
	Point const point{-3.0, 4.0, 5.0};
	Matrix<4, 1> const expected {2.0, 1.0, 7.0, 1.0};
	ASSERT_EQUAL(expected, A * asMatrix(point));
}

void testIdentityMatrix() {
	Matrix<5, 5> const expected {
		1.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 1.0
	};
	ASSERT_EQUAL(expected, identity<5>);
}

void testMultiplicationIdentityWithMatrix() {
	Matrix<4, 4> const expected {
		24.0,  49.0,  98.0, 196.0,
		31.0,  64.0, 128.0, 256.0,
		38.0,  79.0, 158.0, 316.0,
		45.0,  94.0, 188.0, 376.0
	};
	ASSERT_EQUAL(expected, identity<4> * expected);
}

void testMultiplicationMatrixWithIdentity() {
	Matrix<4, 4> const expected {
		24.0,  49.0,  98.0, 196.0,
		31.0,  64.0, 128.0, 256.0,
		38.0,  79.0, 158.0, 316.0,
		45.0,  94.0, 188.0, 376.0
	};
	ASSERT_EQUAL(expected, expected * identity<4>);
}

void testTransposeMatrix() {
	Matrix<4, 4> const matrix {
		24.0,  49.0,  98.0, 196.0,
		31.0,  64.0, 128.0, 256.0,
		38.0,  79.0, 158.0, 316.0,
		45.0,  94.0, 188.0, 376.0
	};
	Matrix<4, 4> const expected {
		24.0,  31.0,  38.0,  45.0,
		49.0,  64.0,  79.0, 94.0,
		98.0, 128.0, 158.0, 188.0,
	   196.0, 256.0, 316.0, 376.0
	};
	ASSERT_EQUAL(expected, transpose(matrix));
}

void testTwoByTwoDeterminant() {
	Matrix<2, 2> const matrix {
		 1.0, 5.0,
		-3.0, 2.0
	};
	double expected{17.0};
	ASSERT_EQUAL(expected, determinant(matrix));
}

void testSubmatrixOfThreeByThree() {
	Matrix<3, 3> const matrix {
		 1.0,  5.0,  0.0,
		-3.0,  2.0,  7.0,
		 0.0,  6.0, -3.0
	};
	Matrix<2, 2> const expected {
		-3.0,  2.0,
		 0.0,  6.0
	};
	ASSERT_EQUAL(expected, submatrix(matrix, 0_row, 2_column));
}

void testSubmatrixFourByFour() {
	Matrix<4, 4> const matrix {
		-6.0,  1.0,  1.0,  6.0,
		-8.0,  5.0,  8.0,  6.0,
		-1.0,  0.0,  8.0,  2.0,
		-7.0,  1.0, -1.0,  1.0
	};
	Matrix<3, 3> const expected {
		-6.0,  1.0,  6.0,
		-8.0,  8.0,  6.0,
		-7.0, -1.0,  1.0
	};
	ASSERT_EQUAL(expected, submatrix(matrix, 2_row, 1_column));
}

void testMinorOfThreeByThree() {
	Matrix<3, 3> const matrix {
		3.0,  5.0,  0.0,
		2.0, -1.0, -7.0,
		6.0, -1.0,  5.0
	};
	ASSERT_EQUAL(25, minor(matrix, 1_row, 0_column));
}

void testDeterminantOfSubmatrix() {
	Matrix<3, 3> const matrix {
		3.0,  5.0,  0.0,
		2.0, -1.0, -7.0,
		6.0, -1.0,  5.0
	};
	Matrix<3, 3> const expected {
		-12.0,  52.0,  4.0,
		 25.0,  15.0, -33.0,
		-35.0, -21.0, -13.0
	};
	Matrix<3, 3> const minors = minorsOf(matrix);
	ASSERT_EQUAL(expected, minors);
}


void testCofactors() {
	Matrix<3, 3> const matrix {
		3.0,  5.0,  0.0,
		2.0, -1.0, -7.0,
		6.0, -1.0,  5.0
	};
	Matrix<3, 3> const expected {
		-12.0, -52.0,  4.0,
		-25.0,  15.0,  33.0,
		-35.0,  21.0, -13.0
	};
	Matrix<3, 3> const cofactors = cofactorsOf(matrix);
	ASSERT_EQUAL(expected, cofactors);
}

void testDeterminantOfThreeByThree() {
	Matrix<3, 3> const matrix {
		 1.0,  2.0,  6.0,
		-5.0,  8.0, -4.0,
		 2.0,  6.0,  4.0
	};
	ASSERT_EQUAL(-196, determinant(matrix));
}

void testDeterminantOfFourByFour() {
	Matrix<4, 4> const matrix {
		-2.0, -8.0,  3.0,  5.0,
		-3.0,  1.0,  7.0,  3.0,
		 1.0,  2.0, -9.0,  6.0,
		-6.0,  7.0,  7.0, -9.0
	};
	ASSERT_EQUAL(-4071, determinant(matrix));
}

void testIsInvertibleWhenDeterminantIsNotZero() {
	Matrix<4, 4> const matrix {
		 6.0,  4.0,  4.0,  4.0,
		 5.0,  5.0,  7.0,  6.0,
		 4.0, -9.0,  3.0, -7.0,
		-6.0,  7.0,  7.0, -9.0
	};
	ASSERT(invertible(matrix));
}

void testIsNotInvertibleWhenDeterminantIsZero() {
	Matrix<4, 4> const matrix {
		-4.0,  2.0, -2.0, -3.0,
		 9.0,  6.0,  2.0,  6.0,
		 0.0, -5.0,  1.0, -5.0,
		 0.0,  0.0,  0.0,  0.0
	};
	ASSERT(!invertible(matrix));
}

void testCofactorsForInversion_step1() {
	Matrix<4, 4> const matrix {
		-5.0,  2.0,  6.0, -8.0,
		 1.0, -5.0,  1.0,  8.0,
		 7.0,  7.0, -6.0, -7.0,
		 1.0, -3.0,  7.0,  4.0
	};
	Matrix<4, 4> const expected {
		 116.0, -430.0, - 42.0, -278.0,
		 240.0, -775.0, -119.0, -433.0,
		 128.0, -236.0, - 28.0, -160.0,
		- 24.0,  277.0,  105.0,  163.0
	};
	ASSERT_EQUAL(expected, cofactorsOf(matrix));
}

void testTransposedCofactorsForInversion_step2() {
	Matrix<4, 4> const cofactors {
		 116.0, -430.0, - 42.0, -278.0,
		 240.0, -775.0, -119.0, -433.0,
		 128.0, -236.0, - 28.0, -160.0,
		- 24.0,  277.0,  105.0,  163.0
	};
	Matrix<4, 4> const expected {
		 116.0, 240.0,   128.0, - 24.0,
		-430.0, -775.0, -236.0,  277.0,
		- 42.0, -119.0, - 28.0,  105.0,
		-278.0, -433.0, -160.0,  163.0
	};
	ASSERT_EQUAL(expected, transpose(cofactors));
}

void testOriginalDeterminant_step3() {
	Matrix<4, 4> const matrix {
		-5.0,  2.0,  6.0, -8.0,
		 1.0, -5.0,  1.0,  8.0,
		 7.0,  7.0, -6.0, -7.0,
		 1.0, -3.0,  7.0,  4.0
	};
	ASSERT_EQUAL(532, determinant(matrix));
}

void testDivideTransposedByDeterminant_step4() {
	Matrix<4, 4> const transposed {
		 116.0, 240.0,   128.0, - 24.0,
		-430.0, -775.0, -236.0,  277.0,
		- 42.0, -119.0, - 28.0,  105.0,
		-278.0, -433.0, -160.0,  163.0
	};
	double const determinant = 532;
	Matrix<4, 4> const expected {
		 0.218045,  0.451128,  0.240602, -0.045113,
		-0.808271, -1.456767, -0.443609,  0.520677,
		-0.078947, -0.223684, -0.052632,  0.197368,
		-0.522556, -0.813910, -0.300752,  0.306391
	};
	ASSERT_EQUAL(expected, transposed / determinant);
}

void testInverseOfMatrixWithDeterminantZeroThrows() {
	Matrix<4, 4> const matrix {
		-4.0,  2.0, -2.0, -3.0,
		 9.0,  6.0,  2.0,  6.0,
		 0.0, -5.0,  1.0, -5.0,
		 0.0,  0.0,  0.0,  0.0
	};
	ASSERT_THROWS(inverse(matrix), std::invalid_argument);
}

void testInverseMatrix1() {
	Matrix<4, 4> const matrix {
		-5.0,  2.0,  6.0, -8.0,
		 1.0, -5.0,  1.0,  8.0,
		 7.0,  7.0, -6.0, -7.0,
		 1.0, -3.0,  7.0,  4.0
	};
	Matrix<4, 4> const expected {
		 0.218045,  0.451128,  0.240602, -0.045113,
		-0.808271, -1.456767, -0.443609,  0.520677,
		-0.078947, -0.223684, -0.052632,  0.197368,
		-0.522556, -0.813910, -0.300752,  0.306391
	};
	ASSERT_EQUAL(expected, inverse(matrix));
}

void testInverseMatrix2() {
	Matrix<4, 4> const matrix {
		 8.0, -5.0,  9.0,  2.0,
		 7.0,  5.0,  6.0,  1.0,
		-6.0,  0.0,  9.0,  6.0,
		-3.0,  0.0, -9.0, -4.0
	};
	Matrix<4, 4> const expected {
		-0.153846, -0.153846, -0.282051, -0.538462,
		-0.076923,  0.123077,  0.025641,  0.030769,
		 0.358974,  0.358974,  0.435897,  0.923077,
		-0.692308, -0.692308, -0.769231, -1.923077
	};
	ASSERT_EQUAL(expected, inverse(matrix));
}

void testInverseMatrix3() {
	Matrix<4, 4> const matrix {
		 9.0,  3.0,  0.0,  9.0,
		-5.0, -2.0, -6.0, -3.0,
		-4.0,  9.0,  6.0,  4.0,
		-7.0,  6.0,  6.0,  2.0
	};
	Matrix<4, 4> const expected {
		-0.040741, -0.077778,  0.144444, -0.222222,
		-0.077778,  0.033333,  0.366667, -0.333333,
		-0.029012, -0.146296, -0.109259,  0.129630,
		 0.177778,  0.066667, -0.266667,  0.333333
	};
	ASSERT_EQUAL(expected, inverse(matrix));
}

void testMultiplyingAProductByItsInverse() {
	Matrix<4, 4> const matrixA {
		 3.0, -9.0,  7.0,  3.0,
		 3.0, -8.0,  2.0, -9.0,
		-4.0,  4.0,  4.0,  1.0,
		-6.0,  5.0, -1.0,  1.0
	};
	Matrix<4, 4> const matrixB {
		 8.0,  2.0,  2.0,  2.0,
		 3.0, -1.0,  7.0,  0.0,
		 7.0,  0.0,  5.0,  4.0,
		 6.0, -2.0,  0.0,  5.0
	};
	ASSERT_EQUAL(matrixA, matrixA * matrixB * inverse(matrixB));
}

void testInvertIdentityMatrix() {
	auto const ident = identity<4>;
	ASSERT_EQUAL(ident, inverse(ident));
}

void testMultiplyByInverse() {
	Matrix<4, 4> const matrix {
		 3.0, -9.0,  7.0,  3.0,
		 3.0, -8.0,  2.0, -9.0,
		-4.0,  4.0,  4.0,  1.0,
		-6.0,  5.0, -1.0,  1.0
	};
	ASSERT_EQUAL(identity<4>, matrix * inverse(matrix));
}

void testInverseOfTransposeIsTransposeOfInverse() {
	Matrix<4, 4> const matrix {
		 3.0, -9.0,  7.0,  3.0,
		 3.0, -8.0,  2.0, -9.0,
		-4.0,  4.0,  4.0,  1.0,
		-6.0,  5.0, -1.0,  1.0
	};
	ASSERT_EQUAL(inverse(transpose(matrix)), transpose(inverse(matrix)));
}

void testEffectOfModifiedIdentity() {
	auto modifiedIdentiy = identity<4>;
	modifiedIdentiy[1_row, 1_column] = 2.0;
	Matrix<1, 4> const tuple{1.0, 2.0, 3.0, 4.0};
	Matrix<1, 4> const expected{1.0, 4.0, 3.0, 4.0};
	ASSERT_EQUAL(expected, tuple * modifiedIdentiy);
}

cute::suite make_suite_MatrixTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultMatrixIsAllZero));
	s.push_back(CUTE(testMatrixConstructedWithValues));
	s.push_back(CUTE(testTwoTimesTwoMatrix));
	s.push_back(CUTE(testThreeTimesThreeMatrix));
	s.push_back(CUTE(testMultiplyTwoMatrices));
	s.push_back(CUTE(testAsMatrix));
	s.push_back(CUTE(testMultiplyMatrixAndDirection));
	s.push_back(CUTE(testMultiplyMatrixAndPoint));
	s.push_back(CUTE(testIdentityMatrix));
	s.push_back(CUTE(testMultiplicationIdentityWithMatrix));
	s.push_back(CUTE(testMultiplicationMatrixWithIdentity));
	s.push_back(CUTE(testTransposeMatrix));
	s.push_back(CUTE(testTwoByTwoDeterminant));
	s.push_back(CUTE(testSubmatrixOfThreeByThree));
	s.push_back(CUTE(testSubmatrixFourByFour));
	s.push_back(CUTE(testMinorOfThreeByThree));
	s.push_back(CUTE(testDeterminantOfSubmatrix));
	s.push_back(CUTE(testCofactors));
	s.push_back(CUTE(testDeterminantOfThreeByThree));
	s.push_back(CUTE(testDeterminantOfFourByFour));
	s.push_back(CUTE(testIsInvertibleWhenDeterminantIsNotZero));
	s.push_back(CUTE(testIsNotInvertibleWhenDeterminantIsZero));
	s.push_back(CUTE(testCofactorsForInversion_step1));
	s.push_back(CUTE(testTransposedCofactorsForInversion_step2));
	s.push_back(CUTE(testOriginalDeterminant_step3));
	s.push_back(CUTE(testDivideTransposedByDeterminant_step4));
	s.push_back(CUTE(testInverseOfMatrixWithDeterminantZeroThrows));
	s.push_back(CUTE(testInverseMatrix1));
	s.push_back(CUTE(testInverseMatrix2));
	s.push_back(CUTE(testInverseMatrix3));
	s.push_back(CUTE(testMultiplyingAProductByItsInverse));
	s.push_back(CUTE(testInvertIdentityMatrix));
	s.push_back(CUTE(testMultiplyByInverse));
	s.push_back(CUTE(testInverseOfTransposeIsTransposeOfInverse));
	s.push_back(CUTE(testEffectOfModifiedIdentity));
	return s;
}
