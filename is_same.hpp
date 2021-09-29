#ifndef IS_SAME_HPP
#define IS_SAME_HPP
#include "types_traits.hpp"
namespace ft { 
	template <class __T, class __U> struct is_same : public false_type {};
	template <class __T> struct is_same<__T, __T>  : public true_type {};
}
#endif
