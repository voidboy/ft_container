#ifndef FT_TYPES_TRAITS_HPP
#define FT_TYPES_TRAITS_HPP
namespace ft {

	/* http://www.cplusplus.com/reference/type_traits/integral_constant/ */
	template <typename T, T v>
	struct integral_constant {
		static const T value = v;
		/*
		typedef T value_type;
		typedef integral_constant<T,v> type;
		inline operator T() { return v; }
		*/
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;
}
#endif
