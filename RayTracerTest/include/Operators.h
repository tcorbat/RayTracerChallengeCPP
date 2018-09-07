#ifndef OPERATORS_H_
#define OPERATORS_H_

namespace operators {

template <typename T, typename U = T>
struct addable {
	constexpr friend auto operator+(T lhs, U const & rhs) {
		return lhs += rhs;
	}

	constexpr friend auto operator+(U const & lhs, T rhs) {
		return rhs += lhs;
	}
};

template <typename T>
struct addable<T, T> {
	constexpr friend auto operator+(T lhs, T const & rhs) {
		return lhs += rhs;
	}
};

template <typename T, typename U = T>
struct subtractable {
	constexpr friend auto operator-(T lhs, U const & rhs) {
		return lhs -= rhs;
	}
};

template <typename T, typename U = T>
struct multipliable {
	constexpr friend auto operator*(T lhs, U const & rhs) {
		return lhs *= rhs;
	}

	constexpr friend auto operator*(U const & lhs, T rhs) {
		return rhs *= lhs;
	}
};

template <typename T>
struct multipliable<T, T> {
	constexpr friend auto operator*(T lhs, T const & rhs) {
		return lhs *= rhs;
	}
};

template <typename T, typename U = T>
struct dividable {
	constexpr friend auto operator/(T lhs, U const & rhs) {
		return lhs /= rhs;
	}
};

template <typename T, typename U = T>
struct equality_comparable {
	constexpr friend bool operator==(T const & lhs, U const & rhs) {
		return rhs == lhs;
	}
	constexpr friend bool operator!=(T const & lhs, U const & rhs) {
		return !(lhs == rhs);
	}
	constexpr friend bool operator!=(U const & lhs, T const & rhs) {
		return !(lhs == rhs);
	}
};

template <typename T>
struct equality_comparable<T, T> {
	constexpr friend bool operator!=(T const & lhs, T const & rhs) {
			return !(lhs == rhs);
		}
};

}



#endif /* OPERATORS_H_ */
