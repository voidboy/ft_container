#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
#include "is_same.hpp"
#define _T_stack template <typename T, typename Container>

namespace ft { 
	template <typename T, typename Container = vector<T> > 
	class stack
	{
		public:

		typedef Container							container_type;
		typedef T									value_type;
		typedef typename container_type::size_type	size_type;

		explicit stack(const typename enable_if<is_same<T,
				typename Container::value_type>::value == true, container_type>::type
				& ctnr = container_type());
		bool empty() const;
		void pop();
		void push(const value_type& val);
		size_type size() const;
		value_type& top();
		const value_type& top() const;

		template <class _T, class _Container>
		friend bool operator==(const stack<_T, _Container> & lhs, const stack<_T, _Container> & rhs);

		template <class _T, class _Container>
		friend bool operator<(const stack<_T, _Container> & lhs, const stack<_T, _Container> & rhs);

		protected:

		container_type  c;
	};

	_T_stack stack<T, Container>::stack(const typename enable_if<is_same<T,
			typename Container::value_type>::value == true, container_type>::type
			& ctnr) : 
		c(ctnr)
	{
		;
	}

	_T_stack bool stack<T, Container>::empty() const { return (this->c.size() == 0); } 

	_T_stack void stack<T, Container>::pop() { this->c.pop_back(); } 

	_T_stack void stack<T, Container>::push(const value_type& val) { this->c.push_back(val); }

	_T_stack typename stack<T, Container>::size_type stack<T, Container>::size() const { return this->c.size(); }

	_T_stack typename stack<T, Container>::value_type & stack<T, Container>::top() { return this->c.back(); }

	_T_stack const typename stack<T, Container>::value_type & stack<T, Container>::top() const { return this->c.back(); }

	template <class T, class Container>
  	bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return (lhs.c == rhs.c); }

	template <class T, class Container>
  	bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return !(lhs == rhs); }

	template <class T, class Container>
  	bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return (lhs.c < rhs.c); }

	template <class T, class Container>
  	bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return (rhs < lhs); }

	template <class T, class Container>
  	bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return !(rhs < lhs); }

	template <class T, class Container>
  	bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{ return !(lhs < rhs); }
}
#endif
