#ifndef INCLUDE_VALUETYPE_H_
#define INCLUDE_VALUETYPE_H_

#include <boost/iterator/counting_iterator.hpp>

template <typename T, typename CRTP>
struct ValueType {
	T value;
};


template <typename T>
struct Incrementable {
	friend T & operator++(T & t) {
		++t.value;
		return t;
	}

	friend T operator++(T & t, int) {
		T previous = t;
		t.value++;
		return previous;
	}
};

template <typename T>
struct Decrementable {
	friend T & operator--(T & t) {
		--t.value;
		return t;
	}

	friend T operator--(T & t, int) {
		T previous = t;
		t.value--;
		return previous;
	}
};

template <typename T>
struct Addable {
	friend T operator+(T lhs, T rhs){
		return {lhs.value + rhs.value};
	}

	friend T & operator+=(T & lhs, T rhs) {
		lhs.value += rhs.value;
		return lhs;
	}
};

template <typename T>
struct Subtractable {
	friend T operator-(T lhs, T rhs){
		return {lhs.value - rhs.value};
	}

	friend T & operator-=(T & lhs, T rhs) {
		lhs.value -= rhs.value;
		return lhs;
	}
};

template <typename T>
struct Comparable {
	friend bool operator==(T lhs, T rhs) {
			return lhs.value == rhs.value;
		}

	friend bool operator!=(T lhs, T rhs) {
		return !(lhs == rhs);
	}
};

template <typename T>
struct Ordered : Comparable<T> {
	friend bool operator<(T lhs, T rhs) {
		return lhs.value < rhs.value;
	}

	friend bool operator>(T lhs, T rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(T lhs, T rhs) {
		return !(lhs > rhs);
	}

	friend bool operator>=(T lhs, T rhs) {
		return !(lhs < rhs);
	}
};

template <typename T>
struct Printable {
	friend std::ostream & operator<<(std::ostream & out, T t) {
		out << t.value;
		return out;
	}
};

template <typename T>
struct Numeric : Incrementable<T>, Decrementable<T>, Addable<T>, Subtractable<T>, Ordered<T>, Printable<T> {
};


#endif /* INCLUDE_VALUETYPE_H_ */
