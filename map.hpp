#include "RBtree.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "compare.hpp"

#define _T_map template <typename Key, typename T, typename Compare, typename Alloc>
#define _S_map map<Key, T, Compare, Alloc>

namespace ft {
	template <typename Key, typename T, typename Compare = std::less<Key>,
			 typename Alloc = std::allocator<ft::pair<const Key, T> > > 
	class map {

		public:

			typedef RBtree<ft::pair<const Key, T>, Compare, Alloc> _RBtree;
			typedef Key						key_type;
			typedef T						mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare						key_compare;
			typedef Alloc						allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::size_t 					size_type;
			typedef std::ptrdiff_t					difference_type;

			typedef typename _RBtree::iterator 			iterator;
			typedef typename _RBtree::const_iterator 		const_iterator;

			typedef typename _RBtree::const_reverse_iterator	const_reverse_iterator;
			typedef typename _RBtree::reverse_iterator		reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{  
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}  
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map(const key_compare & comp = Compare(),
				const allocator_type & alloc = allocator_type());
			template <class InputIterator>
  			map(InputIterator first, InputIterator last, const key_compare & comp = Compare(),
       			const allocator_type & alloc = allocator_type());
			map(const map & x);
			map & operator=(const map & x);
			mapped_type & operator[] (const key_type & k);
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			iterator begin();
			const_iterator begin() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			pair<iterator,bool> insert(const value_type & val);
			iterator insert(iterator position, const value_type & val);
			template <class InsertIterator>
  			void insert(InsertIterator first, InsertIterator last);

			void erase(iterator position);
			size_type erase(const key_type & k);
			void erase(iterator first, iterator last);
			void swap (map & x);
			void clear(void);
			key_compare key_comp() const;
			value_compare value_comp() const;
			iterator find(const key_type & k);
			const_iterator find(const key_type & k) const;
			size_type count(const key_type & k) const;
			iterator lower_bound(const key_type & k);
			const_iterator lower_bound(const key_type & k) const;
			iterator upper_bound(const key_type & k);
			const_iterator upper_bound(const key_type & k) const;
			ft::pair<iterator, iterator> equal_range(const key_type & k);
			ft::pair<const_iterator, const_iterator> equal_range(const key_type & k) const;
			allocator_type get_allocator() const;

		private:
			RBtree<ft::pair<const Key, T>, value_compare, Alloc> tree;
	};

	_T_map _S_map::map(const typename _S_map::key_compare & comp,
			const typename _S_map::allocator_type & alloc) :
		tree(value_compare(comp), alloc)
	{ 
		; 
	}

	_T_map template <class InputIterator>
		_S_map::map(InputIterator first, InputIterator last, const typename _S_map::key_compare & comp,
				const typename _S_map::allocator_type & alloc) : 
			tree(value_compare(comp), alloc)
	{
		while (first != last)
			tree.add_node(*first++);
	}

	_T_map _S_map::map(const _S_map & x) : 
		tree(x.key_comp(), x.get_allocator())
	{
		insert(x.begin(), x.end());
	}

	_T_map _S_map & _S_map::operator=(const _S_map & x)
	{
		this->tree = x.tree;
		return (*this);
	}

	_T_map typename _S_map::mapped_type & _S_map::operator[] (const typename _S_map::key_type & k) 
	{
		return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
	}

	_T_map bool _S_map::empty() const { return (this->tree.get_size() == 0); }

	_T_map typename _S_map::size_type _S_map::size() const { return this->tree.get_size(); }

	_T_map typename _S_map::size_type _S_map::max_size() const { return this->tree.get_allocator().max_size(); }

	_T_map typename _S_map::iterator _S_map::begin() { return this->tree.begin(); } 

	_T_map typename _S_map::const_iterator _S_map::begin() const { return this->tree.begin(); }

	_T_map typename _S_map::reverse_iterator _S_map::rbegin() { return this->tree.rbegin(); } 

	_T_map typename _S_map::const_reverse_iterator _S_map::rbegin() const { return this->tree.rbegin(); }

	_T_map typename _S_map::iterator _S_map::end() { return this->tree.end(); } 

	_T_map typename _S_map::const_iterator _S_map::end() const { return this->tree.end(); }

	_T_map typename _S_map::reverse_iterator _S_map::rend() { return this->tree.rend(); } 

	_T_map typename _S_map::const_reverse_iterator _S_map::rend() const { return this->tree.rend(); }

	_T_map ft::pair<typename _S_map::iterator,bool> _S_map::insert(const typename _S_map::value_type & val) 
	{ 
		return this->tree.add_node(val); 
	}

	_T_map typename _S_map::iterator _S_map::insert(typename _S_map::iterator position, const typename _S_map::value_type& val) 
	{ 
		(void)position;
		return insert(val).first; 
	}

	_T_map template <class InsertIterator>
 	void _S_map::insert(InsertIterator first, InsertIterator last)
	{
		while (first != last)
			insert(*first++);
	}

	_T_map typename _S_map::size_type _S_map::erase(const typename _S_map::key_type & k) 
	{
		return this->tree.del_node(ft::pair<key_type, mapped_type>(k, mapped_type())); 
	}

	_T_map void _S_map::erase(typename _S_map::iterator first, 
			typename _S_map::iterator last) 
	{ 
		tree.del_node(first, last); 
	}

	_T_map void _S_map::erase(typename _S_map::iterator position)
	{
		tree.del_node(position, position + 1);
	}

	_T_map void _S_map::swap(_S_map & x) 
	{ 
		this->tree.swap(x.tree);
	}

	_T_map void _S_map::clear(void) { this->tree.clear(); }

	_T_map typename _S_map::key_compare _S_map::key_comp() const { return key_compare(); }

	_T_map typename _S_map::value_compare _S_map::value_comp() const { return value_compare(Compare()); }

	_T_map typename _S_map::iterator _S_map::find(const typename _S_map::key_type & k) 
	{
		return this->tree.find(ft::pair<key_type, mapped_type>(k, mapped_type())); 
	}

	_T_map typename _S_map::const_iterator _S_map::find(const typename _S_map::key_type & k) const
	{
		return this->tree.find(ft::pair<key_type, mapped_type>(k, mapped_type())); 
	}

	_T_map typename _S_map::size_type _S_map::count(const typename _S_map::key_type & k) const
	{ 
		return this->tree.count(ft::pair<key_type, mapped_type>(k, mapped_type())); 
	}

	_T_map typename _S_map::iterator _S_map::lower_bound(const typename _S_map::key_type & k)
	{
		return this->tree.lower_bound(ft::pair<key_type, mapped_type>(k, mapped_type()));
	}

	_T_map typename _S_map::const_iterator _S_map::lower_bound(const typename _S_map::key_type & k) const 
	{
		return this->tree.lower_bound(ft::pair<key_type, mapped_type>(k, mapped_type()));
	}

	_T_map typename _S_map::iterator _S_map::upper_bound(const typename _S_map::key_type & k)
	{
		return this->tree.upper_bound(ft::pair<key_type, mapped_type>(k, mapped_type()));
	}

	_T_map typename _S_map::const_iterator _S_map::upper_bound(const typename _S_map::key_type & k) const
	{
		return this->tree.upper_bound(ft::pair<key_type, mapped_type>(k, mapped_type()));
	}

	_T_map ft::pair<typename _S_map::iterator, typename _S_map::iterator> 
	_S_map::equal_range(const typename _S_map::key_type & k)
	{
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	_T_map ft::pair<typename _S_map::const_iterator, typename _S_map::const_iterator> 
	_S_map::equal_range(const typename _S_map::key_type & k) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

	_T_map typename _S_map::allocator_type _S_map::get_allocator() const { return this->tree.get_allocator(); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
 	bool operator!=(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
 	bool operator<(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
 	bool operator<=(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
 	bool operator>(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
 	bool operator>=(const map<Key, T,Compare,Alloc>& lhs, const map<Key, T,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}
