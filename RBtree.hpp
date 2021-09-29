#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <iostream>
#include <cstddef>
#include "node.hpp"
#include "pair.hpp"
#include "compare.hpp"
#include "RBtree_iterator.hpp"
#include "reverse_iterator.hpp"
#define _T_RBtree template <typename T, typename Compare, typename Alloc>
#define _S_RBtree RBtree<T, Compare, Alloc>

namespace ft { 

	template <typename T, typename Compare = std::less<T>, 
			typename Alloc = std::allocator<T> >
	class RBtree {
		
	public:
	typedef typename Alloc::template rebind<node<T> >::other	allocator_type;
	typedef typename allocator_type::value_type					value_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef node<T>												Node;
	typedef typename allocator_type::size_type					size_type;

	typedef RBtree_iterator<T>									iterator;
	typedef RBtree_iterator<const T>							const_iterator;

	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:

	Compare			comp;
	Node			*root;
	Node			*NIL;
	size_t			size;
	allocator_type	pool;

	public:

	RBtree(const Compare & fcntl = Compare(),
			const allocator_type & alloc = allocator_type());
	RBtree(const RBtree & ref);
	~RBtree(void);
	Node * get_root(void) const;
	size_t get_size(void) const;
	allocator_type get_allocator(void) const;
	Compare value_comp() const;
	iterator begin(void);
	const_iterator begin(void) const;
	reverse_iterator rbegin(void);
	const_reverse_iterator rbegin(void) const;
	iterator end(void); 
	const_iterator end(void) const;
	reverse_iterator rend(void); 
	const_reverse_iterator rend(void) const;
	void display(Node * root = NULL, std::string pad = "") const;
	ft::pair<iterator, bool> add_node(const T & v);
	size_type del_node(Node * found);
	size_type del_node(const T & v);
	void del_node(iterator first, iterator last);
	void postfix(Node * root, void (RBtree::*f)(Node *));
	RBtree & operator=(const RBtree & rhs);
	void swap(RBtree & ref);
	iterator find(const T & v) const;
	size_type count(const T & k) const ;
	void clear(void);
	iterator lower_bound(const T & key) const;
	iterator upper_bound(const T & key) const;

	private: 

	Node * MINIMUM(void) const;
	Node * MAXIMUM(void) const;
	Node * create_node(const T & v);
	void delete_node(Node * to_delete);
	Node * in_order_successor(Node * n) const;
	Node * in_order_predecessor(Node * n) const;
	Node * search_node(const T & v) const;
	void transplant(Node * donor, Node * recipient);
	void fix_add_node(Node * n);
	void fix_del_node(Node * n);
	void rotation(Node * origin, dir d);
	};

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::get_root(void) const { return this->root; }

	_T_RBtree size_t _S_RBtree::get_size(void) const { return this->size; }

	_T_RBtree typename _S_RBtree::allocator_type _S_RBtree::get_allocator(void) const { return this->pool; }

	_T_RBtree Compare _S_RBtree::value_comp() const { return this->comp; }

	_T_RBtree typename _S_RBtree::iterator _S_RBtree::begin(void) { return iterator(MINIMUM()); }

	_T_RBtree typename _S_RBtree::const_iterator _S_RBtree::begin(void) const { return iterator(MINIMUM()); }

	_T_RBtree typename _S_RBtree::reverse_iterator _S_RBtree::rbegin(void) { return reverse_iterator(this->end()); }

	_T_RBtree typename _S_RBtree::const_reverse_iterator _S_RBtree::rbegin(void) const { return reverse_iterator(this->end()); }

	_T_RBtree typename _S_RBtree::iterator _S_RBtree::end(void) { return iterator(this->NIL); }

	_T_RBtree typename _S_RBtree::const_iterator _S_RBtree::end(void) const { return iterator(this->NIL); }

	_T_RBtree typename _S_RBtree::reverse_iterator _S_RBtree::rend(void) { return reverse_iterator(this->begin()); }

	_T_RBtree typename _S_RBtree::const_reverse_iterator _S_RBtree::rend(void) const { return reverse_iterator(this->begin()); }

	_T_RBtree _S_RBtree::RBtree(const Compare & fcntl,
			const typename _S_RBtree::allocator_type & alloc) : 
		comp(fcntl),
		size(0),
		pool(alloc)
	{
		try { 
			this->NIL = this->pool.allocate(1);
			this->root = this->NIL;
			this->pool.construct(this->NIL, node<T>(T()));
		} 
		catch (std::bad_alloc & e) 
		{  std::cout << e.what() << std::endl; }
	}

	_T_RBtree _S_RBtree::RBtree(const RBtree & ref) : 
		comp(ref.value_comp()),
		size(0),
		pool(ref.get_allocator())
	{
		try { 
			this->NIL = this->pool.allocate(1);
			this->root = this->NIL;
			this->pool.construct(this->NIL, node<T>(T()));
		} 
		catch (std::bad_alloc & e) 
		{  std::cout << e.what() << std::endl; }

		*this = ref;
	}

	_T_RBtree _S_RBtree::~RBtree(void)
	{
		postfix(this->root, &RBtree::delete_node);
		delete_node(this->NIL);
	}
	
	_T_RBtree void _S_RBtree::display(_S_RBtree::Node * root, std::string pad) const
	{
		if (root != this->NIL)
		{
			if (root == root->parent->right)
				std::cout << pad << "├──" << (root->c == RED ? "\e[31m" : "\e[92m") << root->val << "\e[0m" << std::endl;
			else if (root == root->parent->left)
				std::cout << pad << "└──" << (root->c == RED ? "\e[31m" : "\e[92m") << root->val << "\e[0m" << std::endl;
			else 
				std::cout << pad << "   " << "\e[92m" << root->val << "\e[0m" << std::endl;
			display(root->right, pad + ((root == root->parent->left || root->parent == this->NIL ) ? "   " : "│   "));
			display(root->left,  pad + ((root == root->parent->left || root->parent == this->NIL ) ? "   " : "│   "));
		}
	}

	_T_RBtree ft::pair<typename _S_RBtree::iterator, bool> _S_RBtree::add_node(const T & v)
	{
		Node * new_node = NULL;
		Node * leaf = this->root;
		Node * beaf = this->NIL;
		Node * last = this->NIL->parent;

		if (this->size)
		{
			while (leaf != this->NIL)
			{
				beaf = leaf;
				if (comp(v, leaf->val))
					leaf = leaf->left;
				else if (comp(leaf->val, v))
					leaf = leaf->right;
				else if (!comp(leaf->val, v) && !comp(v, leaf->val))
					return ft::pair<iterator, bool>(iterator(leaf), false);
			}
			new_node = create_node(v);
			new_node->parent = beaf;
			new_node->c = RED;
			if (comp(v, beaf->val))
				beaf->left = new_node;
			else
				beaf->right = new_node;
			fix_add_node(new_node);
		}
		else
		{
			this->root = create_node(v);
			new_node = this->root;
		}
		this->size++;
		if (!last)
			this->NIL->parent = MAXIMUM();
		else if (comp(last->val, v))
			this->NIL->parent = new_node;
		return ft::pair<iterator, bool>(iterator(new_node), true);
	}

	_T_RBtree typename _S_RBtree::size_type _S_RBtree::del_node(_S_RBtree::Node * found)
	{
		if (found && found != this->NIL)
		{
			Node * last = this->NIL->parent;
			Node * bak;
			Node * tmp = found;
			color tmpc = tmp->c;
			if (found->left == this->NIL)
			{
				bak = found->right;
				transplant(found, found->right);
			}
			else if (found->right == this->NIL)
			{
				bak = found->left;
				transplant(found, found->left);
			}
			else
			{
				tmp = in_order_successor(found);
				tmpc = tmp->c;
				bak = tmp->right;
				if (tmp->parent == found)
					bak->parent = tmp;
				else
				{
					transplant(tmp, tmp->right);
					tmp->right = found->right;
					tmp->right->parent = tmp;
				}
				transplant(found, tmp);
				tmp->left = found->left;
				tmp->left->parent = tmp;
				tmp->c = found->c;
			}
			this->size--;
			if (found == last)
				this->NIL->parent = found->parent;
			delete_node(found);
			if (tmpc == BLACK)
				fix_del_node(bak);
			return size_type(1);
		}
		return size_type(0);
	}

	_T_RBtree typename _S_RBtree::size_type _S_RBtree::del_node(const T & v) 
	{ 
		return del_node(search_node(v)); 
	}

	_T_RBtree void _S_RBtree::del_node(typename _S_RBtree::iterator first, typename _S_RBtree::iterator last)
	{
		Node * d;
		while (first != last)
		{
			d = first.base();
			first++;
			del_node(d);
		}
	}

	_T_RBtree void _S_RBtree::postfix(_S_RBtree::Node * root, void (_S_RBtree::*f)(_S_RBtree::Node *))
	{
		if (root != this->NIL)
		{
			postfix(root->left, f);
			postfix(root->right, f);
			(this->*f)(root);
		}
	}

	_T_RBtree _S_RBtree & _S_RBtree::operator=(const _S_RBtree & rhs)
	{
		iterator it = rhs.begin();
		this->clear();
		while (it != rhs.end())
			this->add_node(*it++);
		return (*this);
	}

	_T_RBtree void _S_RBtree::swap(_S_RBtree & ref)
	{
		ft::swapp(this->root, ref.root);
		ft::swapp(this->NIL, ref.NIL);
		ft::swapp(this->size, ref.size);
	}

	_T_RBtree typename _S_RBtree::iterator _S_RBtree::find(const T & v) const 
	{ 
		return iterator(search_node(v)); 
	}

	_T_RBtree typename _S_RBtree::size_type _S_RBtree::count(const T & k) const 
	{
		if (search_node(k) != this->NIL)
			return size_type(1);
		else
			return size_type(0);
	}

	_T_RBtree void _S_RBtree::clear(void) 
	{ 
		this->del_node(this->begin(), this->end()); 
	}

	_T_RBtree typename _S_RBtree::iterator _S_RBtree::lower_bound(const T & key) const
	{
		Node * found = search_node(key);
		Node * last = this->NIL;

		if (found && found != this->NIL)
			return iterator(found);
		else
		{
			Node * current = this->root;
			while (1)
			{
				/* key < current->val */
				if (comp(key, current->val))
					last = current;
				if (comp(key, current->val))
				{
					if (current->left == this->NIL)
						break ;
					current = current->left;
				}
				else 
				{
					if (current->right == this->NIL)
						break;
					current = current->right;
				}
				
			}
			return iterator(last);
		}
	}

	_T_RBtree typename _S_RBtree::iterator _S_RBtree::upper_bound(const T & key) const
	{
		Node * found = search_node(key);

		if (found && found != this->NIL)
		{
			if (found->right != this->NIL)
				return in_order_successor(found);
			while (found->parent != this->NIL)
			{
				if (comp(key, found->val))
					return iterator(found);
				found = found->parent;
			}
			return this->end();
		}
		else
		{
			Node * current = this->root;
			while (1)
			{
				if (comp(key, current->val))
				{
					if (current->left != this->NIL)
						current = current->left;
					else 
						return iterator(current);
				}
				else 
				{
					if (current->right != this->NIL)
						current = current->right;
					else
						break ;
				}
			}
			if (current->right != this->NIL)
				return in_order_successor(current);
			else 
			{
				while (current->parent != this->NIL)
				{
					if (comp(key, current->val))
						return iterator(current);
					current = current->parent;
				}
			}
			return this->end();
		}
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::MINIMUM(void) const
	{
		Node * root = this->root;

		if (root != this->NIL)
			while (root->left != this->NIL)
				root = root->left;
		return root;
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::MAXIMUM(void) const
	{
		Node * root = this->root;

		if (root != this->NIL)
			while (root->right != this->NIL)
				root = root->right;
		return root;
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::create_node(const T & v)
	{
		Node * new_node = this->pool.allocate(1);
		this->pool.construct(new_node, node<T>(v, this->NIL));
		return new_node;
	}

	_T_RBtree void _S_RBtree::delete_node(_S_RBtree::Node * to_delete)
	{
		this->pool.destroy(to_delete);
		this->pool.deallocate(to_delete, 1);
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::in_order_successor(_S_RBtree::Node * n) const
	{
		Node * root = n->right;
		if (root == this->NIL)
			return n;
		while (root->left != this->NIL)
			root = root->left;
		return root;
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::in_order_predecessor(_S_RBtree::Node * n) const
	{
		Node * root = n->left;
		if (root == this->NIL)
			return n;
		while (root->right != this->NIL)
			root = root->right;
		return root;
	}

	_T_RBtree typename _S_RBtree::Node * _S_RBtree::search_node(const T & v) const
	{
		Node * root = this->root;
		while (root != this->NIL)
		{
			if (!comp(root->val, v) && !comp(v, root->val))
				break ;
			else if (comp(v, root->val))
				root = root->left;
			else
				root = root->right;
		}
		return (root);
	}

	_T_RBtree void _S_RBtree::transplant(typename _S_RBtree::Node * donor, typename _S_RBtree::Node * recipient)
	{
		if (donor->parent == this->NIL)
			this->root = recipient;
		else if (donor == donor->parent->left)
			donor->parent->left = recipient;
		else
			donor->parent->right = recipient;
		recipient->parent = donor->parent;
	}

	_T_RBtree void _S_RBtree::fix_add_node(typename _S_RBtree::Node * n)
	{
		while (n->parent->c == RED)
		{
			dir		d = LEFT;
			Node *	tmp;

			if (n->parent == n->uncle(LEFT))
				d = RIGHT;
			tmp = n->uncle(d);
			if (tmp->c == RED)
			{
				n->parent->c = BLACK;
				tmp->c = BLACK;
				n->grand_parent()->c = RED;
				n = n->grand_parent();
			}
			else 
			{
				if (n == n->parent->child(d))
				{
					n = n->parent;
					rotation(n, !d);
				}
				n->parent->c = BLACK;
				n->grand_parent()->c = RED;
				rotation(n->grand_parent(), d);
			}
		}
		this->root->c = BLACK;
	}

	_T_RBtree void _S_RBtree::fix_del_node(typename _S_RBtree::Node * n)
	{
		while (n != this->root && n->parent != this->NIL && n->c == BLACK)
		{
			dir		d = RIGHT;
			Node *	tmp;

			if (n == n->parent->left)
				d = LEFT;
			tmp = n->parent->child(!d);
			if (tmp->c == RED)
			{
				tmp->c = BLACK;
				n->parent->c = RED;
				rotation(n->parent, d);
				tmp = n->parent->child(!d);
			}
			if (tmp->child(d)->c == BLACK && 
				tmp->child(!d)->c == BLACK)
			{
				tmp->c = RED;
				n = n->parent;
			}
			else
			{
				if (tmp->child(!d)->c == BLACK)
				{
					tmp->child(d)->c = BLACK;
					tmp->c = RED;
					rotation(tmp, !d);
					tmp = n->parent->child(!d);
				}
				tmp->c = n->parent->c;
				n->parent->c = BLACK;
				tmp->child(!d)->c = BLACK;
				rotation(n->parent, d);
				n = this->root;
			}
		}
		n->c = BLACK;
	}
	
	_T_RBtree void _S_RBtree::rotation(typename _S_RBtree::Node * origin, dir d)
	{
		Node * tmp = origin->child(!d);

		origin->set_child(!d, tmp->child(d));
		if (tmp->child(d) != this->NIL)
			tmp->child(d)->parent = origin;
		tmp->parent = origin->parent;
		if (origin->parent == this->NIL)
			this->root = tmp;
		else if (origin == origin->parent->child(d))
			origin->parent->set_child(d, tmp);
		else
			origin->parent->set_child(!d, tmp);
		tmp->set_child(d, origin);
		origin->parent = tmp;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const _S_RBtree & lhs, const _S_RBtree & rhs )
	{
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const _S_RBtree & lhs, const _S_RBtree & rhs )
	{
		return !(lhs == rhs);
	}
}
#endif
