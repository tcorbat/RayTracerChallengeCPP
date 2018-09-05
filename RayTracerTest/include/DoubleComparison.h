#ifndef DOUBLECOMPARISON_H_
#define DOUBLECOMPARISON_H_


#include <cmath>
#include <cstddef>

template <typename T, typename = std::enable_if<std::is_floating_point_v<T>>>
constexpr T epsilon = 0.000001;

template <typename T, typename = std::enable_if<std::is_floating_point_v<T>>>
constexpr inline bool isEqual(T const lhs, T const rhs) noexcept {
	return std::abs(lhs - rhs) < epsilon<T>;
}


constexpr inline std::size_t roundDouble(double const value) {
	auto const roundedValue = std::lround(value);
	return static_cast<std::size_t>(roundedValue);
}

#endif /* DOUBLECOMPARISON_H_ */
