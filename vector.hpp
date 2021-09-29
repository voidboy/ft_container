#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include "is_integral.hpp"
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "compare.hpp"
#include "types_traits.hpp"
#include "enable_if.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
#define _T_vector template <typename T, typename Alloc>
#define _S_vector vector<T, Alloc>

namespace ft {

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {

		public:

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::size_t 								size_type;
			typedef std::ptrdiff_t								difference_type;

			typedef vector_iterator<pointer>					iterator;
			typedef vector_iterator<const_pointer>				const_iterator;

			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;

			explicit vector(const allocator_type & alloc = allocator_type());
			explicit vector(size_type n, const T & val = value_type(),
				const allocator_type & alloc = allocator_type());
			template <typename InputIterator>
         		vector(typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const allocator_type& alloc = allocator_type());
			vector (const vector & x);
			~vector(void);
			vector & operator=(const vector & x);
			iterator begin(void);
			const_iterator begin(void) const;
			iterator end(void);
			const_iterator end(void) const;
			reverse_iterator rbegin(void);
			const_reverse_iterator rbegin() const;
			reverse_iterator rend(void);
			const_reverse_iterator rend() const;
			size_type size(void) const;
			size_type max_size(void) const;
			void resize(size_type n, value_type val = value_type());
			size_type capacity(void) const;
			bool empty(void) const;
			void reserve(size_type n) throw(std::length_error);
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			reference at(size_type n) throw(std::out_of_range);
			const_reference at(size_type n) const throw(std::out_of_range);
			reference front(void); 
			const_reference front(void) const;
			reference back(void);
			const_reference back(void) const;
			template <typename _U, typename _V>
			void assign(_U a, _V b);
			void push_back(const value_type& val);
			void pop_back(); 
			iterator insert(iterator position, const value_type & val);
			template <typename _U, typename _V>
			void insert(iterator a, _U b, _V c);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void clear();
			allocator_type get_allocator() const;
			void swap(vector & x);

		private:

			void __clear_nd_resize(size_type n);
			void __resize_nd_fill(size_type n, value_type val = value_type());
			void __yycopy(vector const & ref);
			void __insert_dispatch(iterator position, size_type n, const value_type& val, true_type);
			template <class InputIterator>
    		void __insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type);
			void __assign_dispatch(size_type n, const value_type & val, true_type);
			template <typename InputIterator>
			void __assign_dispatch(InputIterator first, InputIterator last, false_type);

			Alloc				pool;
			T *					C;
			size_type			_size;
			size_type			_capacity;
	};

	_T_vector _S_vector::vector(const typename _S_vector::allocator_type & alloc) : 
		pool(alloc),
		C(NULL),
		_size(0),
		_capacity(0)
	{
		;
	}

	_T_vector _S_vector::vector(typename _S_vector::size_type n, const T & val,
		const typename _S_vector::allocator_type & alloc) : 
		pool(alloc),
		C(pool.allocate(n)),
		_size(n),
		_capacity(n)
	{
		for (size_type i = 0; i < n; i++)
			this->pool.construct(this->C + i, val);
	}

	_T_vector template <typename InputIterator>
		_S_vector::vector(typename enable_if<!is_integral<InputIterator>::value,
				InputIterator>::type first, InputIterator last,
				const typename _S_vector::allocator_type & alloc)
		{
			size_type n = std::distance(first, last);
			this->pool = alloc;
			this->C = pool.allocate(n);
			this->_size = n;
			this->_capacity = n;
			for (int i = 0; first != last; i++)
				this->pool.construct(this->C + i, *first++);
		}

	_T_vector _S_vector::vector(const _S_vector & x) : 
		pool(x.get_allocator()),
		_size(0),
		_capacity(0)
	{
		this->assign(x.begin(), x.end());
	}

	_T_vector _S_vector::~vector(void) 
	{
		for (size_type i = 0; i < this->_size; i++)
			this->pool.destroy(this->C + i);
		if (this->_capacity)
			this->pool.deallocate(this->C, this->_capacity);
	}

	_T_vector _S_vector & _S_vector::operator=(const _S_vector & x)
	{
		this->assign(x.begin(), x.end());
		return (*this);
	}

	_T_vector typename _S_vector::iterator _S_vector::begin(void) { return iterator(this->C); }

	_T_vector typename _S_vector::const_iterator _S_vector::begin(void) const { return const_iterator(this->C); }

	_T_vector typename _S_vector::iterator _S_vector::end(void) { return iterator(this->C + this->_size); }

	_T_vector typename _S_vector::const_iterator _S_vector::end(void) const { return const_iterator(this->C + this->_size); }

	_T_vector typename _S_vector::reverse_iterator _S_vector::rbegin(void) { return reverse_iterator(this->end()); }

	_T_vector typename _S_vector::const_reverse_iterator _S_vector::rbegin(void) const { return reverse_iterator(this->end()); }

	_T_vector typename _S_vector::reverse_iterator _S_vector::rend(void) { return reverse_iterator(this->begin()); }

	_T_vector typename _S_vector::const_reverse_iterator _S_vector::rend(void) const { return reverse_iterator(this->begin()); }

	_T_vector typename _S_vector::size_type _S_vector::size(void) const { return this->_size; }

	_T_vector typename _S_vector::size_type _S_vector::max_size(void) const { return this->pool.max_size(); }

	_T_vector void _S_vector::resize(typename _S_vector::size_type n, typename _S_vector::value_type val)
	{
		if (n < this->_size)
			for (size_type i = n; i < this->_size; i++)
				this->pool.destroy(this->C + i);	
		else if (n > this->_size)
		{
			if (n > this->_capacity)
				__resize_nd_fill(n, val);
			else
				for (size_type i = this->_size; i < n; i++)
					this->pool.construct(this->C + i, val);	
		}
		this->_size = n;
	}

	_T_vector typename _S_vector::size_type _S_vector::capacity(void) const { return this->_capacity; }

	_T_vector bool _S_vector::empty(void) const { return this->_size == 0; }

	_T_vector void _S_vector::reserve(typename _S_vector::size_type n) throw(std::length_error)
	{
		if (n > this->max_size())
			throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
		else if (n > this->_capacity)
		{
			T * tmp = this->pool.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
				tmp[i] = (*this)[i];
			this->pool.deallocate(this->C, this->_capacity);
			this->C = tmp;
			this->_capacity = n;
		}
	}

	_T_vector typename _S_vector::reference _S_vector::operator[](typename _S_vector::size_type n) 
	{ 
		return this->C[n]; 
	}

	_T_vector typename _S_vector::const_reference _S_vector::operator[](typename _S_vector::size_type n) const 
	{ 
		return this->C[n]; 
	}

	_T_vector typename _S_vector::reference _S_vector::at(typename _S_vector::size_type n) throw(std::out_of_range)
	{ 
		if (n < 0 || n >= this->_size)
			throw std::out_of_range("out of range index");
		return this->C[n]; 
	}

	_T_vector typename _S_vector::const_reference _S_vector::at(typename _S_vector::size_type n) const throw(std::out_of_range)
	{ 
		if (n < 0 || n >= this->_size)
			throw std::out_of_range("out of range index");
		return this->C[n]; 
	}

	_T_vector typename _S_vector::reference _S_vector::front(void) { return *(this->C); }

	_T_vector typename _S_vector::const_reference _S_vector::front(void) const { return *(this->C); }

	_T_vector typename _S_vector::reference _S_vector::back(void) { return *(this->C + this->_size - 1); }

	_T_vector typename _S_vector::const_reference _S_vector::back(void) const { return *(this->C + this->_size - 1); }

	_T_vector template <typename _U, typename _V>
		void _S_vector::assign(_U a, _V b)
		{
			__assign_dispatch(a, b, is_integral<_U>());
		}

	_T_vector void _S_vector::push_back(const typename _S_vector::value_type & val)
	{
		if (this->_size == this->_capacity)
		{
			if (!this->_capacity)
			{
				this->C = this->pool.allocate(1);
				this->pool.construct(this->C, val);	
				this->_capacity = 1;
			}
			else 
			{
				T * tmp = this->pool.allocate(this->_capacity * 2);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->pool.construct(tmp + i, (*this)[i]);
					this->pool.destroy(this->C + i);
				}
				this->pool.construct(tmp + this->_size, val);	
				this->pool.deallocate(this->C, this->_capacity);
				this->C = tmp;
				this->_capacity *= 2;
			}
		}
		else
			this->pool.construct(this->C + this->_size, val);	
		this->_size++;
	}

	_T_vector void _S_vector::pop_back() { this->pool.destroy(this->C + --this->_size); }


	_T_vector template <typename _U, typename _V>
		void _S_vector::insert(iterator a, _U b, _V c)
		{
			__insert_dispatch(a, b, c, is_integral<_U>());
		}

	_T_vector typename _S_vector::iterator _S_vector::erase(typename _S_vector::iterator position)
	{
		iterator next = position + 1;
		if (next == this->end())
			this->pool.destroy(this->C);
		else
		{
			size_type i = 0;
			for (; next + i != this->end(); i++)
				position[i] = next[i];
			this->pool.destroy(next.base() + --i);
		}
		this->_size--;
		return next;
	}

	_T_vector typename _S_vector::iterator _S_vector::erase(typename _S_vector::iterator first,
			typename _S_vector::iterator last)
	{
		iterator end = this->end();
		this->_size -= std::distance(first, last);
		for (size_type i = 0; last + i != end;)
			*first++ = *(last.base() + i++);
		while (first != end)
			this->pool.destroy(first++.base());
		return (last + 1);
	}

	_T_vector void _S_vector::clear() 
	{
		for (size_type i = 0; i < this->_size; i++)
			this->pool.destroy(this->C + i);	
		this->_size = 0;
	}

	_T_vector typename _S_vector::allocator_type _S_vector::get_allocator() const { return this->pool; }

	_T_vector void _S_vector::swap(_S_vector & x)
	{
		ft::swapp(this->_size, x._size);
		ft::swapp(this->C, x.C);
		ft::swapp(this->_capacity, x._capacity);
	}

	_T_vector void _S_vector::__clear_nd_resize(typename _S_vector::size_type n)
	{
		this->clear();
		if (this->_capacity)
			this->pool.deallocate(this->C, this->_capacity);
		this->C = this->pool.allocate(n);
		this->_capacity = n;
	}

	_T_vector void _S_vector::__resize_nd_fill(typename _S_vector::size_type n, 
			typename _S_vector::value_type val)
	{
		T * tmp = this->pool.allocate(n);
		for (size_type i = 0; i < this->_size; i++)
			tmp[i] = (*this)[i];
		for (size_type i = this->_size; i < n; i++)
			this->pool.construct(tmp + i, val);	
		this->pool.deallocate(this->C, this->_capacity);
		this->C = tmp;
		this->_capacity = n;
		this->_size = n;
	}

	_T_vector void _S_vector::__yycopy(_S_vector const & ref)
	{
		size_type i = 0;
		for (; i < this->_size; i++)
			(*this)[i] = ref[i];
		for (; i < ref._size; i++)
			this->pool.construct(this->C + i, ref[i]);
		this->_size = i;
	}

	_T_vector typename _S_vector::iterator _S_vector::insert(typename _S_vector::iterator position, 
			const typename _S_vector::value_type & val)
	{
		size_type n = position - this->begin();
		__insert_dispatch(position, 1, val, true_type());
		return iterator(this->C + n);
	}

	_T_vector void _S_vector::__insert_dispatch(typename _S_vector::iterator position,
			typename _S_vector::size_type n, const typename _S_vector::value_type & val, true_type)
	{
		if (position == this->end())
			while (n--)
				this->push_back(val);
		else
		{
			if (this->_size + n < this->_capacity)
			{
				if (this->_size + n < this->_capacity)
				{
					iterator back = this->end() - 1 + n;
					iterator copy = this->end() - 1;
					while (copy >= position)
					{
						if (back >= this->end())
							this->pool.construct(back.base(), *copy);
						else 
							*back = *copy;
						--back;
						--copy;
					}
					size_type save_n = n;
					while (save_n--)
					{
						if (position >= this->end())
							this->pool.construct(position.base(), val);
						else 
							*position = val;
						++position;
					}
					this->_size += n;
				}
			}
			else
			{
				iterator	it = this->begin();
				size_type	i;
				size_type	new_size = this->_size + n; 
				T *			tmp = this->pool.allocate(new_size);
				for (i = 0; it + i != position; i++)
				{
					this->pool.construct(tmp + i, it[i]);
					this->pool.destroy(it.base() + i);
				}
				for (size_type j = n; j > 0; j--)
					this->pool.construct(tmp + i++, val);
				for (; it + i - n != this->end(); i++)
				{
					this->pool.construct(tmp + i, it[i - n]);
					this->pool.destroy(it.base() + i - n);
				}
				this->pool.deallocate(this->C, this->_capacity);
				this->C = tmp;
				this->_size = this->_size + n;
				this->_capacity = new_size;
			}
		}
	}

	_T_vector template <class InputIterator>
		void _S_vector::__insert_dispatch(typename _S_vector::iterator position,
				InputIterator first, InputIterator last, false_type)
	{
		if (first == last)
			return ;
		else if (position == this->end())
			while (first != last)
				this->push_back(*first++);
		else 
		{
			size_type n = std::distance(first, last);
			if (this->_size + n < this->_capacity)
			{
				iterator back = this->end() - 1 + n;
				iterator copy = this->end() - 1;
				while (copy >= position)
				{
					if (back >= this->end())
						this->pool.construct(back.base(), *copy);
					else 
						*back = *copy;
					--back;
					--copy;
				}
				while (first != last)
				{
					if (position >= this->end())
						this->pool.construct(position.base(), *first);
					else 
						*position = *first;
					++first;
					++position;
				}
				this->_size += n;
			}
			else
			{
				iterator	it = this->begin();
				size_type	i;
				size_type	new_size = this->_size + n;
				T *			tmp = this->pool.allocate(new_size);
				for (i = 0; it + i != position; i++)
				{
					this->pool.construct(tmp + i, it[i]);
					this->pool.destroy(it.base() + i);
				}
				while (first != last)
					this->pool.construct(tmp + i++, *first++);
				for (; it + i - n != this->end(); i++)
				{
					this->pool.construct(tmp + i, it[i - n]);
					this->pool.destroy(it.base() + i - n);
				}
				this->pool.deallocate(this->C, this->_capacity);
				this->C = tmp;
				this->_size = this->_size + n;
				this->_capacity = new_size;
			}
		}
	}

	_T_vector void _S_vector::__assign_dispatch(typename _S_vector::size_type n,
			const typename _S_vector::value_type & val, true_type)
	{
		if (this->_capacity < n)
			__clear_nd_resize(n);
		for (size_type i = 0; i < n; i++)
		{
			if (i < this->_size)
			{
				this->pool.destroy(this->C + i);
				this->pool.construct(this->C + i, val);
			}
			else
				this->pool.construct(this->C + i, val);
		}
		this->_size = n;
	}

	_T_vector template <typename InputIterator>
		void _S_vector::__assign_dispatch(InputIterator first, InputIterator last, false_type)
		{
			size_type n = std::distance(first, last);
			if (this->_capacity < n)
				__clear_nd_resize(n);
			for (size_type i = 0; first != last; first++, i++)
			{
				if (i < this->_size)
				{
					this->pool.destroy(this->C + i);
					this->pool.construct(this->C + i, *first);
				}
				else
					this->pool.construct(this->C + i, *first);
			}
			this->_size = n;

		}

	template <class T, class Alloc>
		bool operator==(const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template <class T, class Alloc>
		bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs < rhs);
		}

	template <class T, class Alloc>
		void swap(vector<T,Alloc> & x, vector<T,Alloc> & y)
	{
		x.swap(y);
	}
}
#endif
