#ifndef FT_RBTREE_CONST_ITERATOR_HPP
#define FT_RBTREE_CONST_ITERATOR_HPP
#include "RBtree_iterator.hpp"
#include "node.hpp"
#define _T_RBtree_const_iterator template <typename T>

namespace ft { 
	template <typename T>
	class RBtree_const_iterator 
	{
		public:

		typedef const T &						reference;
		typedef const T *						pointer;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const node<T> 					Node;
		typedef const node<T> * 				ptrNode;
		typedef std::bidirectional_iterator_tag	iterator_category;

		RBtree_const_iterator(void);
		RBtree_const_iterator(const ptrNode & n);
		explicit RBtree_const_iterator(const RBtree_const_iterator & n);
		template <typename Type>
		RBtree_const_iterator(const RBtree_const_iterator<Type> & n);
		template <typename Type>
		RBtree_const_iterator(const RBtree_iterator<Type> & n);
		reference operator*() const;
		pointer operator->() const; 
		RBtree_const_iterator operator++(int);
		RBtree_const_iterator operator++();
		RBtree_const_iterator operator--(int);
		RBtree_const_iterator operator--();
		RBtree_const_iterator operator-(const difference_type & n);
		RBtree_const_iterator operator+(const difference_type & n);
		RBtree_const_iterator & operator=(const RBtree_const_iterator & rhs);
		bool operator!=(const RBtree_const_iterator & rhs) const;
		bool operator==(const RBtree_const_iterator & rhs) const;
		bool operator<(const RBtree_const_iterator & rhs) const;
		bool operator>(const RBtree_const_iterator & rhs) const;
		ptrNode base(void) const;

		protected:

		ptrNode current_node;
	};

	_T_RBtree_const_iterator RBtree_const_iterator<T>::RBtree_const_iterator(void) : 
		current_node(NULL)
	{
		;
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T>::RBtree_const_iterator(const ptrNode & n) : 
		current_node(n)
	{
		;
	}

	_T_RBtree_const_iterator
	RBtree_const_iterator<T>::RBtree_const_iterator(const RBtree_const_iterator & n) : 
		current_node(n.base())
	{
		;
	}

	_T_RBtree_const_iterator template <typename Type>
	RBtree_const_iterator<T>::RBtree_const_iterator(const RBtree_const_iterator<Type> & n) : 
		current_node(n.base())
	{
		;
	}

	_T_RBtree_const_iterator template <typename Type>
	RBtree_const_iterator<T>::RBtree_const_iterator(const RBtree_iterator<Type> & n) : 
		current_node(n.base())
	{
		;
	}

	_T_RBtree_const_iterator typename RBtree_const_iterator<T>::reference RBtree_const_iterator<T>::operator*() const
	{ 
		return current_node->val; 
	}

	_T_RBtree_const_iterator typename RBtree_const_iterator<T>::pointer RBtree_const_iterator<T>::operator->() const
	{ 
		return std::addressof(current_node->val);
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator++(int) 
	{
		RBtree_const_iterator old(*this);

		if (current_node->right->is_nill_node())
		{
			if (current_node == current_node->parent->right)
			{
				while (current_node == current_node->parent->right)
					current_node = current_node->parent;
				current_node = current_node->parent;
			}
			else 
				current_node = current_node->parent;
		}
		else
		{
			current_node = current_node->right;
			while (!current_node->left->is_nill_node())
				current_node = current_node->left;	
		}
		return old;
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator++() 
	{
		(*this)++;
		return (*this);
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator--(int) 
	{
		RBtree_const_iterator old(*this);

		if (current_node->is_nill_node())
			current_node = current_node->parent;
		else if (current_node->left->is_nill_node())
		{
			if (current_node == current_node->parent->left)
			{
				while (current_node == current_node->parent->left)
					current_node = current_node->parent;
				current_node = current_node->parent;
			}
			else 
				current_node = current_node->parent;
		}
		else
		{
			current_node = current_node->left;
			while (!current_node->right->is_nill_node())
				current_node = current_node->right;	
		}
		return old;
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator--() 
	{
		(*this)--;
		return (*this);
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator-(const difference_type & n) 
	{ 
		difference_type i = n;
		RBtree_const_iterator tmp(*this);

		while (i--)
			tmp--;
		return tmp; 
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> RBtree_const_iterator<T>::operator+(const difference_type & n) 
	{ 
		difference_type i = n;
		RBtree_const_iterator tmp(*this);

		while (i--)
			tmp++;
		return tmp; 
	}

	_T_RBtree_const_iterator RBtree_const_iterator<T> & RBtree_const_iterator<T>::operator=(const RBtree_const_iterator & rhs)
	{
		this->current_node = rhs.current_node;
		return (*this);
	}

	_T_RBtree_const_iterator typename RBtree_const_iterator<T>::Node * RBtree_const_iterator<T>::base(void) const { return current_node; }

	_T_RBtree_const_iterator bool RBtree_const_iterator<T>::operator!=(const RBtree_const_iterator & rhs) const 
	{ return current_node != rhs.current_node; }

	_T_RBtree_const_iterator bool RBtree_const_iterator<T>::operator==(const RBtree_const_iterator & rhs) const 
	{ return current_node == rhs.current_node; }

	_T_RBtree_const_iterator bool RBtree_const_iterator<T>::operator>(const RBtree_const_iterator & rhs) const 
	{ return current_node > rhs.current_node; }

	_T_RBtree_const_iterator bool RBtree_const_iterator<T>::operator<(const RBtree_const_iterator & rhs) const 
	{ return current_node < rhs.current_node; }
} 
#endif
