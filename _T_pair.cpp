#include <cassert>
#include "pair.hpp"

static void constructor_default(void)
{
	ft::pair<int, int> a;
	assert(a.first == 0);
	assert(a.second == 0);
}

static void constructor_copy(void)
{
	ft::pair<int, int> a;
	ft::pair<int, int> b(a);
	assert(b.first == 0);
	assert(b.second == 0);
}

static void constructor_param(void)
{
	ft::pair<int, int> a(24,42);
	assert(a.first == 24);
	assert(a.second == 42);
}

static void operator_equal(void)
{
	ft::pair<int, int> a(24,42);
	ft::pair<int, int> b;
	assert((b = a) == b);
	assert(b.first == 24);
	assert(b.second == 42);
}

static void make_pair_great_again(void)
{
	ft::pair<int, int> a = ft::make_pair(24,42);
	assert(a.first == 24);
	assert(a.second == 42);
}

static void relational_operator(void)
{
	ft::pair<int, int> a(1,2);
	ft::pair<int, int> b(3,4);
	assert(!(a == b));
	assert(a != b);
	assert(a < b);
	assert(a <= b);
	assert(b > a);
	assert(b >= a);
}

void pair_tests(void)
{
	constructor_default();
	constructor_copy();
	constructor_param();
	operator_equal();
	make_pair_great_again();
	relational_operator();
}
