#ifndef FT_RBTREE_ITERATOR_HPP
#define FT_RBTREE_ITERATOR_HPP
#include "node.hpp"
#define _T_RBtree_iterator template <typename T>

namespace ft { 
	template <typename T>
	class RBtree_iterator 
	{
		public:

		typedef T &								reference;
		typedef T *								pointer;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef node<T> 						Node;
		typedef node<T> * 						ptrNode;
		typedef std::bidirectional_iterator_tag	iterator_category;

		RBtree_iterator(void);
		RBtree_iterator(const ptrNode & n);
		explicit RBtree_iterator(const RBtree_iterator & n);
		template <typename Type>
		RBtree_iterator(const RBtree_iterator<Type> & n);
		T & operator*(); 
		T & operator*() const; 
		pointer operator->(); 
		pointer operator->() const;
		RBtree_iterator operator++(int);
		RBtree_iterator operator++();
		RBtree_iterator operator--(int);
		RBtree_iterator operator--();
		RBtree_iterator operator-(const difference_type & n);
		RBtree_iterator operator+(const difference_type & n);
		RBtree_iterator & operator=(const RBtree_iterator & rhs);
		bool operator!=(const RBtree_iterator & rhs) const;
		bool operator==(const RBtree_iterator & rhs) const;
		bool operator<(const RBtree_iterator & rhs) const;
		bool operator>(const RBtree_iterator & rhs) const;
		ptrNode base(void) const;

		protected:

		ptrNode current_node;
	};

	_T_RBtree_iterator RBtree_iterator<T>::RBtree_iterator(void) : 
		current_node(NULL)
	{
		;
	}

	_T_RBtree_iterator RBtree_iterator<T>::RBtree_iterator(const ptrNode & n) : 
		current_node(n)
	{
		;
	}

	_T_RBtree_iterator
	RBtree_iterator<T>::RBtree_iterator(const RBtree_iterator & n) : 
		current_node(n.base())
	{
		;
	}

	_T_RBtree_iterator template <typename Type>
	RBtree_iterator<T>::RBtree_iterator(const RBtree_iterator<Type> & n) : 
		current_node(reinterpret_cast<ptrNode>(n.base()))
	{
		;
	}

	_T_RBtree_iterator T & RBtree_iterator<T>::operator*() { return current_node->val; }

	_T_RBtree_iterator T & RBtree_iterator<T>::operator*() const { return current_node->val; }

	_T_RBtree_iterator T * RBtree_iterator<T>::operator->() 
	{ 
		return std::__addressof(current_node->val);
	}

	_T_RBtree_iterator T * RBtree_iterator<T>::operator->() const 
	{ 
		return std::__addressof(current_node->val);
	}

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator++(int) 
	{
		RBtree_iterator old(*this);

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

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator++() 
	{
		(*this)++;
		return (*this);
	}

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator--(int) 
	{
		RBtree_iterator old(*this);

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

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator--() 
	{
		(*this)--;
		return (*this);
	}

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator-(const difference_type & n) 
	{ 
		difference_type i = n;
		RBtree_iterator tmp(*this);

		while (i--)
			tmp--;
		return tmp; 
	}

	_T_RBtree_iterator RBtree_iterator<T> RBtree_iterator<T>::operator+(const difference_type & n) 
	{ 
		difference_type i = n;
		RBtree_iterator tmp(*this);

		while (i--)
			tmp++;
		return tmp; 
	}

	_T_RBtree_iterator RBtree_iterator<T> & RBtree_iterator<T>::operator=(const RBtree_iterator & rhs)
	{
		this->current_node = rhs.current_node;
		return (*this);
	}

	_T_RBtree_iterator typename RBtree_iterator<T>::Node * RBtree_iterator<T>::base(void) const { return current_node; }

	_T_RBtree_iterator bool RBtree_iterator<T>::operator!=(const RBtree_iterator & rhs) const 
	{ return current_node != rhs.current_node; }

	_T_RBtree_iterator bool RBtree_iterator<T>::operator==(const RBtree_iterator & rhs) const 
	{ return current_node == rhs.current_node; }

	_T_RBtree_iterator bool RBtree_iterator<T>::operator>(const RBtree_iterator & rhs) const 
	{ return current_node > rhs.current_node; }

	_T_RBtree_iterator bool RBtree_iterator<T>::operator<(const RBtree_iterator & rhs) const 
	{ return current_node < rhs.current_node; }
} 
#endif
