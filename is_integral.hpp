#ifndef FT_IS_INTEGRAL_HPP
#define FT_IS_INTEGRAL_HPP
#include "types_traits.hpp"
namespace ft {

	template <typename> struct is_integral : public false_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
}
#endif
