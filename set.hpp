#include "RBtree.hpp"
#include "compare.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#define _T_set template <typename T, typename Compare, typename Alloc>
#define _S_set set<T, Compare, Alloc>

namespace ft {
	template <typename T, typename Compare = std::less<T>,
			 typename Alloc = std::allocator<T> > 
	class set {

		public:

			typedef RBtree<T> _RBtree;

			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::size_t 								size_type;
			typedef std::ptrdiff_t								difference_type;

			typedef typename _RBtree::const_iterator 					iterator;
			typedef typename _RBtree::const_iterator 					const_iterator;

			typedef typename _RBtree::const_reverse_iterator				reverse_iterator;
			typedef typename _RBtree::const_reverse_iterator				const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{  
				friend class set<T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}  
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x, y);
					}
			};

			explicit set(const key_compare & comp = Compare(),
			const allocator_type & alloc = allocator_type());
			template <class InputIterator>
  			set(InputIterator first, InputIterator last, const key_compare & comp = Compare(),
       		const allocator_type & alloc = allocator_type());
			set(const set & x);
			set & operator=(const set & x);
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
			ft::pair<iterator,bool> insert(const value_type & val);
			iterator insert(iterator position, const value_type& val);
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last);
			void erase(iterator position);
			size_type erase(const value_type & k);
			void erase(iterator first, iterator last);
			void swap(set & x);
			void clear(void);
			key_compare key_comp() const;
			value_compare value_comp() const;
			iterator find(const value_type & k) const;
			size_type count(const key_type & k) const;
			iterator lower_bound(const value_type & k);
			const_iterator lower_bound(const value_type & k) const;
			iterator upper_bound(const value_type & k);
			const_iterator upper_bound(const value_type & k) const;
			ft::pair<iterator, iterator> equal_range(const key_type & k);
			ft::pair<const_iterator, const_iterator> equal_range(const key_type & k) const;
			allocator_type get_allocator() const; 

		private:
			RBtree<T, value_compare, Alloc> tree;
	};

	_T_set _S_set::set(const typename _S_set::key_compare & comp,
			const typename _S_set::allocator_type & alloc) :
		tree(value_compare(comp), alloc)
	{ 
		; 
	}

	_T_set template <class InputIterator>
	_S_set::set(InputIterator first, InputIterator last,
			const typename _S_set::key_compare & comp,
			const typename _S_set::allocator_type & alloc) : 
			tree(value_compare(comp), alloc)
	{
		while (first != last)
			tree.add_node(*first++);
	}

	_T_set _S_set::set(const set & x) : 
		tree(x.key_comp(), x.get_allocator())
	{
		insert(x.begin(), x.end());
	}

	_T_set _S_set & _S_set::operator=(const set & x)
	{
		this->tree = x.tree;
		return (*this);
	}

	_T_set bool _S_set::empty() const 
	{ 
		return (this->tree.get_size() == 0); 
	}

	_T_set typename _S_set::size_type _S_set::size() const 
	{ 
		return this->tree.get_size(); 
	}

	_T_set typename _S_set::size_type _S_set::max_size() const 
	{ 
		return this->tree.get_allocator().max_size(); 
	}

	_T_set typename _S_set::iterator _S_set::begin() 
	{ 
		return this->tree.begin(); 
	}

	_T_set typename _S_set::const_iterator _S_set::begin() const 
	{ 
		return this->tree.begin(); 
	}

	_T_set typename _S_set::reverse_iterator _S_set::rbegin() { return this->tree.rbegin(); } 

	_T_set typename _S_set::const_reverse_iterator _S_set::rbegin() const { return this->tree.rbegin(); }

	_T_set typename _S_set::iterator _S_set::end() { return this->tree.end(); } 

	_T_set typename _S_set::const_iterator _S_set::end() const { return this->tree.end(); }

	_T_set typename _S_set::reverse_iterator _S_set::rend() { return this->tree.rend(); } 

	_T_set typename _S_set::const_reverse_iterator _S_set::rend() const { return this->tree.rend(); }

	_T_set ft::pair<typename  _S_set::iterator,bool> 
	_S_set::insert(const typename _S_set::value_type & val) { return this->tree.add_node(val); }

	_T_set typename _S_set::iterator 
	_S_set::insert(_S_set::iterator position, const _S_set::value_type & val) 
	{ 
		(void)position;
		return insert(val).first; 
	}

	_T_set template <class InputIterator> void _S_set::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			insert(*first++);
	}

	_T_set void _S_set::erase(typename _S_set::iterator position) 
	{
		this->tree.del_node(*position);
	}

	_T_set typename _S_set::size_type _S_set::erase(const typename _S_set::value_type & k) 
	{
		return this->tree.del_node(k); 
	}

	_T_set void _S_set::erase(typename _S_set::iterator first, typename _S_set::iterator last) 
	{ 
		tree.del_node(first, last); 
	}

	_T_set void _S_set::swap(set & x) 
	{ 
		this->tree.swap(x.tree);
	}

	_T_set void _S_set::clear(void) 
	{ 
		this->tree.clear(); 
	}

	_T_set typename _S_set::key_compare _S_set::key_comp() const { return key_compare(); }

	_T_set typename _S_set::value_compare _S_set::value_comp() const { return value_compare(Compare()); }

	_T_set typename _S_set::iterator _S_set::find(const _S_set::value_type & k) const
	{
		return this->tree.find(k);
	}

	_T_set typename _S_set::size_type _S_set::count(const typename _S_set::key_type & k) const
	{ 
		return this->tree.count(k);
	}

	_T_set typename _S_set::iterator _S_set::lower_bound(const typename _S_set::value_type & k) 
	{
		return this->tree.lower_bound(k);
	}

	_T_set typename _S_set::const_iterator _S_set::lower_bound(const typename _S_set::value_type & k) const 
	{
		return this->tree.lower_bound(k);
	}

	_T_set typename _S_set::iterator _S_set::upper_bound(const typename _S_set::value_type & k) 
	{
		return this->tree.upper_bound(k);
	}

	_T_set typename _S_set::const_iterator _S_set::upper_bound(const typename _S_set::value_type & k) const
	{
		return this->tree.upper_bound(k);
	}

	_T_set ft::pair<typename _S_set::iterator, typename _S_set::iterator> 
	_S_set::equal_range(const typename _S_set::key_type & k) 
	{
		return pair<typename _S_set::iterator, typename _S_set::iterator>(lower_bound(k), upper_bound(k));
	}

	_T_set ft::pair<typename _S_set::const_iterator, typename _S_set::const_iterator> 
	_S_set::equal_range(const typename _S_set::key_type & k) const
	{
		return pair<typename _S_set::const_iterator, typename _S_set::const_iterator>(lower_bound(k), upper_bound(k));
	}

	_T_set typename _S_set::allocator_type _S_set::get_allocator() const { return this->tree.get_allocator(); }

	template <class T, class Compare, class Alloc>
	bool operator==(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Compare, class Alloc>
 	bool operator!=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
 	bool operator<(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Compare, class Alloc>
 	bool operator<=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
 	bool operator>(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
 	bool operator>=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
}
