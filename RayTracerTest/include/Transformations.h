#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_


#include "Matrix.h"
#include "Point.h"
#include "Ray.h"

#include <cmath>

template <typename T>
constexpr auto translation(T const & x, T const & y, T const & z) {
	auto result = identity<4>;
	result[0_row, 3_column] = x;
	result[1_row, 3_column] = y;
	result[2_row, 3_column] = z;
	return result;
}

template<typename ValueType = double>
constexpr auto transform(Ray const & ray, Matrix<4, 4, ValueType> const & matrix) {
	return Ray::create(matrix * ray.origin, matrix * ray.direction);
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


template <typename T>
constexpr auto rotation_x(T const & x) {
	auto rotation = identity<4>;
	rotation[1_row, 1_column] = rotation[2_row, 2_column] = std::cos(x);
	rotation[1_row, 2_column] = -std::sin(x);
	rotation[2_row, 1_column] = std::sin(x);
	return rotation;
}

template <typename T>
constexpr auto rotation_y(T const & x) {
	auto rotation = identity<4>;
	rotation[0_row, 0_column] = rotation[2_row, 2_column] = std::cos(x);
	rotation[0_row, 2_column] = std::sin(x);
	rotation[2_row, 0_column] = -std::sin(x);
	return rotation;
}

template <typename T>
constexpr auto rotation_z(T const & x) {
	auto rotation = identity<4>;
	rotation[0_row, 0_column] = rotation[1_row, 1_column] = std::cos(x);
	rotation[0_row, 1_column] = -std::sin(x);
	rotation[1_row, 0_column] = std::sin(x);
	return rotation;
}

template <typename T>
constexpr auto shearing(T const & xToY, T const & xToZ, T const & yToX, T const & yToZ, T const & zToX, T const & zToY) {
	auto shear = identity<4>;
	shear[0_row, 1_column] = xToY;
	shear[0_row, 2_column] = xToZ;
	shear[1_row, 0_column] = yToX;
	shear[1_row, 2_column] = yToZ;
	shear[2_row, 0_column] = zToX;
	shear[2_row, 1_column] = zToY;
	return shear;
}


#endif /* TRANSFORMATIONS_H_ */
