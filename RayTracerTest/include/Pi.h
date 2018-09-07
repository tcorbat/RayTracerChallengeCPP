#ifndef PI_H_
#define PI_H_

#include <boost/math/constants/constants.hpp>

template <typename T>
constexpr auto pi = boost::math::constants::pi<double>();



#endif /* PI_H_ */
