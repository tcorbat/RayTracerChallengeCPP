#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_


#include "Matrix.h"
#include "Point.h"



template <typename T>
constexpr auto translation(T const & x, T const & y, T const & z) {
	auto result = identity<4>;
	result[0_row, 3_column] = x;
	result[1_row, 3_column] = y;
	result[2_row, 3_column] = z;
	return result;
}

namespace {

template <typename ValueType, typename Target>
constexpr Target multiply(Matrix<4, 4, ValueType> const & transformation, Target const & target) {
	auto const transformed = transformation * asMatrix(target);
	return {
			transformed[0_row, 0_column],
			transformed[1_row, 0_column],
			transformed[2_row, 0_column]
		};
}

}

template <typename ValueType>
constexpr Point operator*(Matrix<4, 4, ValueType> const & transformation, Point const & point) {
	return multiply(transformation, point);
}

template <typename ValueType>
constexpr Direction operator*(Matrix<4, 4, ValueType> const & transformation, Direction const & direction) {
	return multiply(transformation, direction);
}

template <typename T>
constexpr auto scaling(T const & x, T const & y, T const & z) {
	auto result = identity<4>;
	result[0_row, 0_column] = x;
	result[1_row, 1_column] = y;
	result[2_row, 2_column] = z;
	return result;
}


#endif /* TRANSFORMATIONS_H_ */
