#ifndef INCLUDE_CANVAS_H_
#define INCLUDE_CANVAS_H_

#include "Color.h"
#include "Index.h"
#include "Point.h"
#include "ValueType.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>



struct CanvasIndex {
	Column const column;
	Row const row;
};

constexpr inline CanvasIndex operator,(Column const column, Row const row) noexcept {
	return {column, row};
}

inline auto createCanvasData(Column const columns, Row const rows) {
	return std::make_unique<Color[]>(rows.value * columns.value);
}

class Canvas {
	Column const columns_;
	Row const rows_;
	std::unique_ptr<Color[]> const data_;

	void checkIndex(CanvasIndex const index) const {
		if (index.row >= rows_ || index.column >= columns_) {
			throw std::invalid_argument{"Canvas index is out of bound"};
		}
	}

	CanvasIndex indexFromPoint(Point const & point) const {
		return {Column{roundDouble(point.x)}, Row{rows_.value - roundDouble(point.y)}};
	}

	std::size_t toAbsoluteOffset(CanvasIndex const index) const {
		return index.row.value * columns_.value + index.column.value;
	}

public:

	explicit Canvas(Column const columns, Row const rows) :
			columns_{columns},
			rows_{rows},
			data_{createCanvasData(columns, rows)} {
	}

	Color & operator[](CanvasIndex const index) {
		checkIndex(index);
		return data_[toAbsoluteOffset(index)];
	}

	Color const & operator[](CanvasIndex const index) const {
		checkIndex(index);
		return data_[toAbsoluteOffset(index)];
	}

	Color & operator[](Point const & point) {
		auto const index = indexFromPoint(point);
		return (*this)[index];
	}

	Color const & operator[](Point const & point) const {
		auto const index = indexFromPoint(point);
		return (*this)[index];
	}

	Row rows() const {
		return rows_;
	}

	Column columns() const {
		return columns_;
	}
};

inline void printPPMHeader(std::ostream & out, Canvas const & canvas) {
	out << "P3\n";
	out << canvas.columns() << ' ' << canvas.rows() << '\n';
	out << "255\n";
}

inline constexpr unsigned colorToUnsigned(double const value) {
	constexpr int minValue { 0u };
	constexpr int maxValue { 255u };
	auto const roundedValue = std::round(value * maxValue);
	auto const unsignedValue = static_cast<int>(roundedValue);
	return std::clamp(unsignedValue, minValue, maxValue);
}

inline constexpr unsigned countDigits(unsigned value) {
	unsigned digits{1};
	while (value /= 10) {
		++digits;
	}
	return digits;
}

inline constexpr unsigned colorOutputWidth(Color const & color) {
	unsigned outputWidth{2};
	outputWidth += countDigits(colorToUnsigned(color.red));
	outputWidth += countDigits(colorToUnsigned(color.green));
	outputWidth += countDigits(colorToUnsigned(color.blue));
	return outputWidth;
}

template <typename Action>
inline void forEachIndex(Canvas const & canvas, Action && action) {
	for (auto row = 0_row; row < canvas.rows(); ++row) {
		for (auto column = 0_column; column < canvas.columns(); ++column) {
			action(CanvasIndex{column, row});
		}
	}
}

inline void printPPMColor(std::ostream & out, Color const & color) {
	out << colorToUnsigned(color.red) << ' ';
	out << colorToUnsigned(color.green) << ' ';
	out << colorToUnsigned(color.blue);
}

inline void printPPMPixelRow(std::ostream & out, Canvas const & canvas, Row const row) {
	std::size_t nOfCharsInRow{};
	for (auto column = 0_column; column < canvas.columns(); ++column) {
		Color const cellColor = canvas[column, row];
		auto const outputWidth = colorOutputWidth(cellColor);
		auto const widthAfterOutput = nOfCharsInRow + outputWidth + !!nOfCharsInRow;
		if (widthAfterOutput > 70) {
			out << '\n';
			nOfCharsInRow = 0;
		}
		if (nOfCharsInRow > 0) {
			out << ' ';
			++nOfCharsInRow;
		}
		printPPMColor(out, cellColor);
		nOfCharsInRow += outputWidth;
	}
}

inline void printPPMPixels(std::ostream & out, Canvas const & canvas) {
	for (auto row = 0_row; row < canvas.rows(); ++row) {
		printPPMPixelRow(out, canvas, row);
		out << '\n';
	}
}

inline void printPPM(std::ostream & out, Canvas const & canvas) {
	printPPMHeader(out, canvas);
	printPPMPixels(out, canvas);
}

#endif /* INCLUDE_CANVAS_H_ */
