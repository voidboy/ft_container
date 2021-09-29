#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP
#include <iostream>

#define _T_pair template <typename T1, typename T2>
namespace ft {

	template <class T1, class T2> 
	class pair { 

	public:

		typedef T1	first_type;
		typedef T2	second_type;

		pair(void);
		template<class U, class V> pair(const pair<U,V>& pr);
		pair(const T1 & a, const T2 & b);
		pair & operator=(const pair & pr);

		T1 first;
		T2 second;
	};

	_T_pair pair<T1, T2>::pair(void) : 
		first(T1()),
		second(T2())
	{
		;
	}

	_T_pair template<class U, class V> 
	pair<T1, T2>::pair(const pair<U,V>& pr) :
		first(pr.first),
		second(pr.second)
	{
		;
	}

	_T_pair pair<T1, T2>::pair(const T1 & a, const T2 & b) :
		first(a),
		second(b)
	{
		;
	}

	_T_pair pair<T1, T2> & pair<T1, T2>::operator=(const pair & pr)
	{
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}

  	_T_pair pair<T1,T2> make_pair (T1 x, T2 y)
	{ return ft::pair<T1, T2>(x, y); }

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return rhs < lhs; }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs)
	{ return !(lhs < rhs); }

	template <class T1, class T2>
	std::ostream & operator<<(std::ostream & os, const pair<T1,T2> & rhs)
	{ 
		os << rhs.first;
		return os;
	}
}
#endif
