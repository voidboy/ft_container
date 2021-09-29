#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#define _T_ri template <typename iterator> 
#define _S_ri reverse_iterator<iterator>
namespace ft {

	template <typename iterator>
	class reverse_iterator
	{
		public:

			typedef typename iterator::value_type		value_type;
			typedef typename iterator::pointer			pointer;
			typedef typename iterator::reference		reference;
			typedef typename iterator::difference_type	difference_type;

			reverse_iterator(void);
			explicit reverse_iterator(const iterator x); 
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it);
			reverse_iterator operator+(const difference_type n);
			reverse_iterator & operator++();
			reverse_iterator operator++(int);
			reverse_iterator & operator+=(difference_type n);
			reverse_iterator operator-(const difference_type n);
			reverse_iterator & operator--();
			reverse_iterator operator--(int);
			reverse_iterator & operator-=(difference_type n);
			iterator base(void) const;
			reference operator[](int index);
			pointer operator->() const;
			reference operator*() const;

		private:

			iterator p;
	};

	_T_ri _S_ri::reverse_iterator(void) :
		p(NULL)
	{
		;
	}

	_T_ri _S_ri::reverse_iterator(const iterator x) : 
		p(x) 
	{
		;		
	}

	_T_ri template <class Iter>
	_S_ri::reverse_iterator(const reverse_iterator<Iter> & x) :
		p(x.base()) 
	{
		;
	}

	_T_ri _S_ri & _S_ri::operator++() 
	{

		--p;
		return *this;
	}

	_T_ri _S_ri _S_ri::operator++(int) 
	{
		reverse_iterator tmp(*this); 
		++(*this); 
		return tmp;
	}

	_T_ri _S_ri & _S_ri::operator+=(difference_type n)
	{
		p -= n;
		return (*this);
	}

	_T_ri _S_ri & _S_ri::operator--() 
	{
		++p;
		return *this;
	}

	_T_ri _S_ri _S_ri::operator--(int) 
	{
		reverse_iterator tmp(*this); 
		--(*this); 
		return tmp;
	}

	_T_ri _S_ri & _S_ri::operator-=(difference_type n)
	{
		p += n;
		return (*this);
	}

	_T_ri iterator _S_ri::base(void) const { return p; }

	_T_ri typename _S_ri::reference _S_ri::operator[](int index) { return *(this->p - index - 1); }

	_T_ri typename _S_ri::pointer _S_ri::operator->() const
	{ 
		return &(this->operator*());
	}

	_T_ri typename _S_ri::reference _S_ri::operator*() const
	{ 
		iterator tmp = p;
		return *--tmp;
	}

	_T_ri _S_ri _S_ri::operator-(const _S_ri::difference_type n) { return reverse_iterator(p + n); }
	_T_ri _S_ri _S_ri::operator+(const _S_ri::difference_type n) { return reverse_iterator(p - n); }

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() == rhs.base(); }

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() != rhs.base(); }

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() > rhs.base(); }

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() >= rhs.base(); }

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() < rhs.base(); }

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) 
	{ return lhs.base() <= rhs.base(); }

	template <typename _Iterator>
	reverse_iterator<_Iterator> operator+(const typename reverse_iterator<_Iterator>::difference_type & lhs,
			const reverse_iterator<_Iterator> & rhs) { return reverse_iterator<_Iterator>(rhs.base() - lhs); }

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs,
			const reverse_iterator<Iterator2>& rhs) 
	{ return rhs.base() - lhs.base(); }
}
#endif
