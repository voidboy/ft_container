#include <cassert>
#include "RBtree.hpp"

static void default_constructor(void)
{
	ft::RBtree<int> tree;

	assert(tree.get_size() == 0);
}

static void RBtree_iterator(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	ft::RBtree<int>::iterator it = tree.begin();
	int i = 1;
	while (it != tree.end())
		assert(i++ == *it++);
	while (it != tree.begin())
		assert(--i == *--it);
	i = 9;
	ft::RBtree<int>::reverse_iterator rt = tree.rbegin();
	while (rt != tree.rend())
		assert(i-- == *rt++);
	while (rt != tree.rbegin())
		assert(++i == *--rt);
}

static void RBtree_add_node(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	assert(tree.get_size() == 9);
}

static void RBtree_del_node(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	tree.del_node(7);
	tree.del_node(9);
	tree.del_node(2);
	tree.del_node(1);
	tree.del_node(5);
	tree.del_node(4);
	tree.del_node(8);
	tree.del_node(6);
	tree.del_node(3);
	tree.del_node(7);
	tree.del_node(9);
	tree.del_node(2);
	tree.del_node(1);
	tree.del_node(5);
	tree.del_node(4);
	tree.del_node(8);
	tree.del_node(6);
	tree.del_node(3);
	assert(tree.get_size() == 0);
}

static void RBtree_clear(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	tree.clear();
	assert(tree.get_size() == 0);
}

static void RBtree_count(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	assert(tree.count(7) == 1);
	assert(tree.count(777) == 0);
	tree.clear();
	assert(tree.count(777) == 0);
	assert(tree.count(7) == 0);
}

static void RBtree_find(void)
{
	ft::RBtree<int> tree;

	tree.add_node(7);
	tree.add_node(9);
	tree.add_node(2);
	tree.add_node(1);
	tree.add_node(5);
	tree.add_node(4);
	tree.add_node(8);
	tree.add_node(6);
	tree.add_node(3);
	assert(*(tree.find(7)) == 7);
	assert(tree.find(777) == tree.end());
}

void btree_tests(void)
{
	default_constructor();
	RBtree_iterator();
	RBtree_add_node();
	RBtree_del_node();
	RBtree_clear();
	RBtree_count();
	RBtree_find();
}
