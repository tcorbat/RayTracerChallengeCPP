#ifndef INDEX_H_
#define INDEX_H_

#include "ValueType.h"

#include <boost/iterator/counting_iterator.hpp>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>


struct Row : ValueType<std::size_t, Row>, Numeric<Row> {};

constexpr inline Row operator""_row(unsigned long long value) noexcept {
	return {value};
}


struct Column : ValueType<std::size_t, Column>, Numeric<Column> {};

constexpr inline Column operator""_column(unsigned long long value) noexcept {
	return {value};
}

namespace std {
template <>
struct iterator_traits<Row> : std::iterator<std::input_iterator_tag, Row> {
};

template <>
struct iterator_traits<Column> : std::iterator<std::input_iterator_tag, Column> {
};
}



template <typename T>
class Range {
	T beginValue;
	T endValue;
public:
	using iterator = boost::counting_iterator<T>;
	
	Range(T begin, T end) : beginValue{std::move(begin)}, endValue{std::move(end)} {
		if (end < begin) {
			throw std::logic_error{"begin cannot be after end"};
		}
	}
	
	iterator begin() const {
		return iterator{beginValue};
	}
	
	iterator end() const {
		return iterator{endValue};
	}
};

#endif /* INDEX_H_ */
