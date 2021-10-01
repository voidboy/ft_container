#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP
#include "iterator_traits.hpp"
#define _T_vi template <typename _Pointer>
#define _S_vi vector_iterator<_Pointer>
namespace ft {

	template <typename _Pointer>
	class vector_iterator 
	{
		typedef iterator_traits<_Pointer> it;

		public:

		typedef typename it::iterator_category	iterator_category;
		typedef typename it::value_type			value_type;
		typedef typename it::pointer			pointer;
		typedef typename it::reference			reference;
		typedef typename it::difference_type	difference_type;

			vector_iterator();
			explicit vector_iterator(const pointer & x);
			template <class iter>
			vector_iterator(const vector_iterator<iter> & x);

			vector_iterator & operator+=(const difference_type & n);
			vector_iterator & operator++();
			vector_iterator operator++(int);
			vector_iterator & operator-=(const difference_type & n);
			vector_iterator & operator--();
			vector_iterator operator--(int);
			bool operator==(const vector_iterator & rhs) const;
			bool operator!=(const vector_iterator & rhs) const;
			reference operator[](difference_type n) const;
			pointer operator->();
			pointer operator->() const;
			reference operator*();
			reference operator*() const;
			vector_iterator operator-(const difference_type & n);
			vector_iterator operator+(const difference_type & n);
			_Pointer base(void) const;

		private:

			_Pointer p;
	};
	
	_T_vi _S_vi::vector_iterator() : 
		p(NULL) 
	{
		;		
	}
	_T_vi _S_vi::vector_iterator(const pointer & x) : 
		p(x) 
	{
		;		
	}

	_T_vi 
	template<class iter>
	_S_vi::vector_iterator(const vector_iterator<iter> & x) : 
		p(x.base()) 
	{
	}

	_T_vi _S_vi & _S_vi::operator++() 
	{
		++p;
		return *this;
	}

	_T_vi _S_vi _S_vi::operator++(int) 
	{
		vector_iterator tmp(*this); 
		++(*this); 
		return tmp;
	}

	_T_vi _S_vi & _S_vi::operator--() 
	{
		--p;
		return *this;
	}

	_T_vi _S_vi _S_vi::operator--(int) 
	{
		vector_iterator tmp(*this); 
		--(*this); 
		return tmp;
	}

	_T_vi bool _S_vi::operator==(const _S_vi & rhs) const { return p == rhs.p; }

	_T_vi bool _S_vi::operator!=(const _S_vi & rhs) const { return p != rhs.p; }

	_T_vi typename _S_vi::reference _S_vi::operator[](difference_type n) const { return this->p[n]; }

	_T_vi typename _S_vi::pointer _S_vi::operator->() { return p;}

	_T_vi typename _S_vi::pointer _S_vi::operator->() const { return p;}

	_T_vi typename _S_vi::reference _S_vi::operator*() { return *p; }

	_T_vi typename _S_vi::reference _S_vi::operator*() const { return *p; }

	_T_vi _S_vi _S_vi::operator-(const typename _S_vi::difference_type & n) 
	{ 
		return vector_iterator(p - n); 
	}

	_T_vi _S_vi _S_vi::operator+(const typename _S_vi::difference_type & n) 
	{ 
		return vector_iterator(p + n); 
	}

	_T_vi _S_vi & _S_vi::operator+=(const typename _S_vi::difference_type & n) 
	{ 
		p += n;
		return (*this);
	}

	_T_vi _S_vi & _S_vi::operator-=(const typename _S_vi::difference_type & n) 
	{ 
		p -= n;
		return (*this);
	}

	_T_vi _Pointer _S_vi::base(void) const { return p; }

	template <typename _Iterator1, typename _Iterator2>
	bool operator<(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() < rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	bool operator<=(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() <= rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	bool operator>(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() > rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	bool operator>=(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() >= rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	typename vector_iterator<_Iterator1>::difference_type operator-(const vector_iterator<_Iterator1> & lhs,
			const vector_iterator<_Iterator2> & rhs) { return lhs.base() - rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	typename vector_iterator<_Iterator1>::difference_type operator+(const vector_iterator<_Iterator1> & lhs,
			const vector_iterator<_Iterator2> & rhs) { return lhs.base() + rhs.base(); }

	template <typename _Iterator>
	vector_iterator<_Iterator> operator+(const typename vector_iterator<_Iterator>::difference_type & lhs,
			const vector_iterator<_Iterator> & rhs) { return vector_iterator<_Iterator>(rhs.base() + lhs); }

	template <typename _Iterator1, typename _Iterator2>
	bool operator==(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() == rhs.base(); }

	template <typename _Iterator1, typename _Iterator2>
	bool operator!=(const vector_iterator<_Iterator1> & lhs, const vector_iterator<_Iterator2> & rhs) 
	{ return lhs.base() != rhs.base(); }
}

#endif
