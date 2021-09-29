#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP
#include <iterator>
#include <cstddef>
/* Modéle : https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01054_source.html#0 */
namespace ft {
	template<typename iterator>
	class iterator_traits
	{
		public:
		typedef typename iterator::iterator_category iterator_category;
		typedef typename iterator::value_type        value_type;
		typedef typename iterator::difference_type   difference_type;
		typedef typename iterator::pointer           pointer;
		typedef typename iterator::reference         reference;
	};

	template<typename T>
	class iterator_traits<T *>
	{
		public:
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T *								pointer;
		typedef T &								reference;
	};

	template<typename T>
	class iterator_traits<const T *>
	{
		public:
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T *						pointer;
		typedef const T &						reference;
	};
}
#endif
