#ifndef FT_NODE_HPP
#define FT_NODE_HPP
#define _T_node template <typename T>
namespace ft { 

	typedef bool dir;

	enum color { 
		RED,
		BLACK,
	};

	enum  { 
		RIGHT = false,
		LEFT = true,
	};	

	template <typename T>
	struct node { 

		node(const T & v = T(), node *nil = NULL);
		explicit node(const node & n);
		template <typename perlinpinpin>
		node(const node<perlinpinpin> & n);
		template <typename perlinpinpin>
		node(const node<perlinpinpin> * & n);
		bool is_nill_node(void) const;
		void set_child(dir d, node * v);
		node * child(dir d);
		node * grand_parent(void);
		node * uncle(dir d); 
	
		color		c;
		node		*parent;
		node		*left;
		node		*right;
		T			val;
	};	
	
	_T_node node<T>::node(const T & v, node *nil) : 
		c(BLACK),
		parent(nil),
		left(nil),
		right(nil),
		val(v)
	{
		;
	}

	_T_node 
	node<T>::node(const node & n) :
		c(n.c),
		parent(n.parent),
		left(n.left),
		right(n.right),
		val(n.val)
	{
		;
	}

	_T_node template <typename perlinpinpin>
	node<T>::node(const node<perlinpinpin> & n) :
		c(n.c),
		parent(n.parent),
		left(n.left),
		right(n.right),
		val(n.val)
	{
		;
	}

	_T_node template <typename perl>
	node<T>::node(const node<perl> * & n) :
		c(n->c),
		parent(n->parent),
		left(n->left),
		right(n->right),
		val(n->val)
	{
		;
	}


	_T_node bool node<T>::is_nill_node(void) const 
	{ 
		return (this->right == NULL && this->left == NULL); 
	}

	_T_node void node<T>::set_child(dir d, node * v)
	{
		if (d == LEFT)
			this->left = v; 
		else 
			this->right = v;
	}

	_T_node node<T> * node<T>::child(dir d) 
	{	
		if (d == LEFT)
			return this->left;
		return this->right;
	}

	_T_node node<T> * node<T>::grand_parent(void) 
	{ 
		return this->parent->parent; 
	}

	_T_node node<T> * node<T>::uncle(dir d) 
	{ 
		if (d == LEFT)
			return this->parent->parent->left;
		return this->parent->parent->right;
	}
}
#endif
