#ifndef MATRIX_H_
#define MATRIX_H_


#include "Coordinate.h"
#include "Direction.h"
#include "DoubleComparison.h"
#include "Index.h"
#include "Point.h"

#include <boost/operators.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <stdexcept>


struct MatrixIndex {
	Row const row;
	Column const column;

	constexpr MatrixIndex(Row const row, Column const column) : row{row}, column{column}{}
};

constexpr inline MatrixIndex operator,(Row const row, Column const column) noexcept {
	return {row, column};
}


template <std::size_t Rows, std::size_t Columns, typename ValueType = double>
struct Matrix  {
	std::array<ValueType, Rows * Columns> values{};

	constexpr std::size_t toAbsoluteOffset(MatrixIndex const index) const {
		if (index.row.value >= Rows) {
			throw std::invalid_argument{"Row access outside of available rows"};
		}
		if (index.column.value >= Columns) {
			throw std::invalid_argument{"Column access outside of available columns"};
		}
		return index.row.value * Columns + index.column.value;
	}

	constexpr ValueType & operator[](MatrixIndex const & index) {
		return values[toAbsoluteOffset(index)];
	}

	constexpr ValueType const & operator[](MatrixIndex const & index) const {
		return values[toAbsoluteOffset(index)];
	}
};

template<std::size_t M, std::size_t N, typename T>
constexpr bool operator==(Matrix<M, N, T> const & lhs, Matrix<M, N, T> const & rhs) {
	return std::equal(
			begin(lhs.values), end(lhs.values), 
			begin(rhs.values), end(rhs.values), 
			[](auto const leftValue, auto const rightValue) {
		if constexpr (std::is_floating_point_v<T>) {
			return isEqual(leftValue, rightValue);
		} else {
			return leftValue == rightValue;
		}
	});
}

template<std::size_t M, std::size_t N, typename T>
constexpr bool operator!=(Matrix<M, N, T> const & lhs, Matrix<M, N, T> const & rhs) {
	return !(lhs == rhs);
}


template<std::size_t M, std::size_t N, typename T>
std::ostream & operator<<(std::ostream & out, Matrix<M, N, T> const & matrix) {
	std::ios_base::fmtflags const flags{out.flags()};
	out << std::fixed << std::setprecision(6);
	out << "Matrix<" << M << ", " << N << ">\n";
	auto counter = 0u;
	for (auto const & value : matrix.values) {
		out << value;
		++counter;
		if (counter % N) {
			out << ", ";
		} else {
			out << '\n';
		}
	}
	out.flags(flags);
	return out;
}

template<std::size_t M, std::size_t N, std::size_t K, typename T>
constexpr auto operator*(Matrix<M, N, T> const & lhs, Matrix<N, K, T> const & rhs) {
	Matrix<M, K, T> result{};
	for (auto targetRow = 0_row; targetRow < Row{M}; ++targetRow) {
		for (auto targetColumn = 0_column; targetColumn < Column{K}; ++targetColumn) {
			T value{};
			for (auto component = 0u; component < N; ++component) {
				value += lhs[targetRow, Column{component}] * rhs[Row{component}, targetColumn];
			}
			result[targetRow, targetColumn] = value;
		}
	}
	return result;
}

template<std::size_t M, std::size_t N, typename T>
constexpr auto operator*=(Matrix<M, N, T> & lhs, T const & factor) {
	for (auto targetRow = 0_row; targetRow < Row{M}; ++targetRow) {
		for (auto targetColumn = 0_column; targetColumn < Column{N}; ++targetColumn) {
			lhs[targetRow, targetColumn] *= factor;
		}
	}
	return lhs;
}

template<std::size_t M, std::size_t N, typename T>
constexpr auto operator*(Matrix<M, N, T> lhs, T const & factor) {
	lhs *= factor;
	return lhs;
}

template<std::size_t M, std::size_t N, typename T>
constexpr auto operator*(T const & factor, Matrix<M, N, T> rhs) {
	return rhs * factor;
}

template<std::size_t M, std::size_t N, typename T>
constexpr auto operator/=(Matrix<M, N, T> & lhs, T const & divisor) {
	for (auto targetRow = 0_row; targetRow < Row{M}; ++targetRow) {
		for (auto targetColumn = 0_column; targetColumn < Column{N}; ++targetColumn) {
			lhs[targetRow, targetColumn] /= divisor;
		}
	}
	return lhs;
}

template<std::size_t M, std::size_t N, typename T>
constexpr auto operator/(Matrix<M, N, T> lhs, T const & divisor) {
	lhs /= divisor;
	return lhs;
}

inline constexpr Matrix<4, 1, double> asMatrix(Direction const & direction) {
	return {direction.x, direction.y, direction.z, 0.0};
}

inline constexpr Matrix<4, 1, double> asMatrix(Point const & point) {
	return {point.x, point.y, point.z, 1.0};
}



template <std::size_t N, std::size_t M, typename T>
constexpr auto transpose(Matrix<N, M, T> const & matrix) {
	Matrix<M, N, T> transposed{};
	for (auto sourceRow = 0_row; sourceRow < Row{M}; ++sourceRow) {
		Column const targetColumn{sourceRow.value};
		for (auto sourceColumn = 0_column; sourceColumn < Column{N}; ++sourceColumn) {
			Row const targetRow{sourceColumn.value};
			transposed[targetRow, targetColumn] = matrix[sourceRow, sourceColumn];
		}
	}
	return transposed;
}

namespace {
	template <std::size_t N, typename T = double>
	constexpr auto fillIdentity() {
		Matrix<N, N, T> result{};
		for (auto i = 0u; i < N; ++i) {
			result[Row{i}, Column{i}] = 1;
		}
		return result;
	}
}

template <std::size_t N, typename T = double>
constexpr Matrix<N, N, T> identity = fillIdentity<N, T>();

template <std::size_t N, std::size_t M, typename T>
constexpr auto submatrix(Matrix<N, M, T> const & matrix, Row skippedRow, Column skippedColumn) {
	Matrix<N - 1, M - 1, T> result{};
	for (auto targetRow = 0_row; targetRow < Row{N - 1}; ++targetRow) {
		auto const sourceRow = targetRow < skippedRow ? targetRow : targetRow + 1_row;
		for (auto targetColumn = 0_column; targetColumn < Column{N - 1}; ++targetColumn) {
			auto const sourceColumn = targetColumn < skippedColumn ? targetColumn : targetColumn + 1_column;
			result[targetRow, targetColumn] = matrix[sourceRow, sourceColumn];
		}
	}
	return result;
}

template <std::size_t N, std::size_t M, typename T>
constexpr T determinant(Matrix<N, M, T> const & matrix);

template <typename T>
constexpr T determinant(Matrix<2, 2, T> const & matrix) {
	return matrix[0_row, 0_column] * matrix[1_row, 1_column] - matrix[0_row, 1_column] * matrix[1_row, 0_column];
}


template <std::size_t N, std::size_t M, typename T>
constexpr auto minor(Matrix<N, M, T> const & matrix, Row skippedRow, Column skippedColumn) {
	auto const sub = submatrix(matrix, skippedRow, skippedColumn);
	return determinant(sub);
}

template <std::size_t N, std::size_t M, typename T>
constexpr T cofactor(Matrix<N, M, T> const & matrix, Row row, Column column) {
	auto const resultMinor = minor(matrix, row, column);
	return (row.value + column.value) % 2 ? -resultMinor : resultMinor;
}

template <std::size_t N, std::size_t M, typename T>
constexpr T determinant(Matrix<N, M, T> const & matrix) {
	T result{};
	for (auto column = 0_column; column < Column{M}; ++column) {
		result += matrix[0_row, column] * cofactor(matrix, 0_row, column);
	}
	return result;
}

template <std::size_t N, std::size_t M, typename T>
constexpr bool invertible(Matrix<N, M, T> const & matrix) {
	return !isEqual(determinant(matrix), T(0));
}

namespace {

template <std::size_t N, std::size_t M, typename T, typename F>
constexpr auto transformCells(Matrix<N, M, T> const & matrix, F function) {
	Matrix<N, M, T> result{};
	for (auto row = 0_row; row < Row{N}; ++row) {
		for (auto column = 0_column; column < Column{M}; ++column) {
			result[row, column] = function(row, column);
		}
	}
	return result;
}

template <std::size_t N, std::size_t M, typename T, typename F>
constexpr void forAllCells(Matrix<N, M, T> const & matrix, F function) {
	for (auto row = 0_row; row < Row{N}; ++row) {
		for (auto column = 0_column; column < Column{M}; ++column) {
			function(row, column);
		}
	}
}

}


template <std::size_t N, std::size_t M, typename T>
constexpr auto cofactorsOf(Matrix<N, M, T> const & matrix) {
	return transformCells(matrix, [&](auto row, auto column) {
		return cofactor(matrix, row, column);
	});
}

template <std::size_t N, std::size_t M, typename T>
constexpr auto minorsOf(Matrix<N, M, T> const & matrix) {
	return transformCells(matrix, [&](auto row, auto column) {
		return minor(matrix, row, column);
	});
}


template <std::size_t N, std::size_t M, typename T>
constexpr auto inverse(Matrix<N, M, T> const & matrix) {
	auto const det = determinant(matrix);
	if (isEqual(det, T(0))) {
		throw std::invalid_argument{"Inverse of matrix with determinant zero is not computable"};
	}
	auto const cofactors = cofactorsOf(matrix);
	auto const transposed = transpose(cofactors);
	return transposed / det;
}


#endif /* MATRIX_H_ */
