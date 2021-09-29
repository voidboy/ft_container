#include <cassert>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "vector.hpp"

static void dump_vector(ft::vector<int> v)
{
	std::cout << "Size: " << v.size() << std::endl;
	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << "> " << v.at(i) << std::endl;
	std::cout << "=====" << std::endl;
}

static void constructor_default(void)
{
	ft::vector<int> a;
	assert(a.size() == 0);
	assert(a.capacity() == 0);
}

static void constructor_fill(void)
{
	ft::vector<int> a(10);
	assert(a.size() == 10);
	assert(a.capacity() == 10);
	for (int i = 0; i < 10; i++)
		assert(a[i] == int());
	ft::vector<int> b(10, 42);
	assert(b.size() == 10);
	assert(b.capacity() == 10);
	for (int i = 0; i < 10; i++)
		assert(b[i] == 42);
}

static void constructor_range(void)
{
	std::vector<int> ref(10);
	ref.push_back(1);
	ref.push_back(2);
	ref.push_back(3);
	ft::vector<int> a(ref.begin(), ref.end());
	assert(std::equal(a.begin(), a.end(), ref.begin()));
	assert(ref.size() == a.size());
	assert(ref.size() == a.capacity());
}

static void constructor_copy(void)
{
	ft::vector<int> ref;
	ref.push_back(1);
	ref.push_back(2);
	ref.push_back(3);
	ft::vector<int> a(ref);
	assert(std::equal(a.begin(), a.end(), ref.begin()));
	assert(a.size() == ref.size());
}

static void operator_equal(void)
{
	ft::vector<int> ref(10, 10);
	ft::vector<int> a;
	assert((a = ref) == ref);
	assert(a.capacity() == ref.size());
	ft::vector<int> bref;
	ft::vector<int> b;
	assert((b = bref) == bref);
	assert(b.capacity() == bref.size());
	ft::vector<int> cref;
	ft::vector<int> c(10,10);
	assert((c = cref) == cref);
}

static void vector_iterator()
{
	ft::vector<int> ref;
	ref.push_back(1);
	ref.push_back(2);
	ref.push_back(3);
	ft::vector<int>::iterator it = ref.begin();
	ft::vector<int>::const_iterator ct = ref.begin();
	assert(it == ct);
	for (int i = 1; it != ref.end(); i++, it++)
		assert(*it == i);
	ft::vector<int> const_ref;
	const_ref.push_back(1);
	ft::vector<int>::const_iterator cit = const_ref.begin();
	assert(cit.operator->()[0] == 1);
}
static void vector_riterator()
{
	ft::vector<int> ref;
	ref.push_back(1);
	ref.push_back(2);
	ref.push_back(3);
	ft::vector<int>::reverse_iterator it = ref.rbegin();
	for (int i = 3; it != ref.rend(); i--, it++)
		assert(*it == i);
}

static void resize(void)
{
	ft::vector<int> foo;
	ft::vector<int> ref(3);
	ft::vector<int> bref(42,42);
	foo.resize(3);
	assert(foo.size() == 3);
	assert(std::equal(foo.begin(), foo.end(), ref.begin()));
	foo.resize(0);
	assert(foo.size() == 0);
	foo.resize(42,42);
	assert(std::equal(foo.begin(), foo.end(), bref.begin()));
}

static void at(void)
{
	ft::vector<int> foo(2, 42);
	assert(42 == foo.at(0));
	try { foo.at(-1); } catch (std::out_of_range const &) { ; } catch (...) { assert(1 == 0); }
	try { foo.at(42); } catch (std::out_of_range const &) { ; } catch (...) { assert(1 == 0); }
}

static void back_nd_front(void)
{
	ft::vector<int> foo(1,42);
	assert(foo.front() == 42);
	assert(foo.back() == 42);
}

static void assign(void)
{
	ft::vector<int> a;
	ft::vector<int> zzz;
	ft::vector<int> ref(10, 42);
	ft::vector<int> lef(1, 42);
	a.assign(10, 42);
	assert(std::equal(a.begin(), a.end(), ref.begin()));
	a.assign(1, 42);
	assert(std::equal(a.begin(), a.end(), lef.begin()));
	a.assign(0, 42);
	assert(std::equal(a.begin(), a.end(), zzz.begin()));
	a.assign(ref.begin(), ref.end());
	assert(std::equal(a.begin(), a.end(), ref.begin()));
}

static void push_back(void)
{
	ft::vector<int> a;
	a.push_back(42);
	assert(a.size() == 1);
	assert(a.capacity() == 1);
	assert(a[0] == 42);
	a.push_back(24);
	assert(a.size() == 2);
	assert(a.capacity() == 2);
	assert(a[1] == 24);
	a.push_back(66);
	assert(a.size() == 3);
	assert(a.capacity() == 4);
	assert(a[2] == 66);
}

static void pop_back(void)
{
	ft::vector<int> a;
	a.push_back(42);
	a.pop_back();
	assert(a.size() == 0);
}

static void erase(void)
{
	ft::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.erase(a.begin() + 1);
	assert(a[0] == 1);
	assert(a[1] == 3);
	ft::vector<int> b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.erase(b.begin(), b.end());
	assert(b.size() == 0);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.erase(b.begin(), b.begin() + 2);
	assert(b.size() == 1);
	assert(b.at(0) == 3);
	b.clear();
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.erase(b.begin() + 1, b.begin() + 2);
	assert(b.size() == 2);
	assert(b.at(0) == 1);
	assert(b.at(1) == 3);
}

static void swap(void)
{
	ft::vector<int> a;
	ft::vector<int> b;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	b.swap(a);
	assert(b[0] == 1);
	assert(b[1] == 2);
	assert(b[2] == 3);
	assert(a.size() == 0);
	a.swap(b);
}



static void insert(void)
{
	ft::vector<int> a;
	a.insert(a.begin(), 3);
	a.insert(a.begin(), 2);
	a.insert(a.begin(), 1);
	for (int i = 0; i < 3; i++)
		assert(i + 1 == a.at(i));
	assert(*(a.insert(a.end(), 4)) == 4);
	assert(*(a.insert(a.begin(), 0)) == 0);
	a.clear();
	a.insert(a.begin(), 1, 3);
	a.insert(a.begin(), 1, 2);
	a.insert(a.begin(), 1, 1);
	for (int i = 0; i < 3; i++)
		assert(i + 1 == a.at(i));
	a.insert(a.end(), 4, 4);
	assert(*(a.end() - 1) == 4);
	a.insert(a.begin(), 1, 0);
	assert(*(a.begin()) == 0);
	ft::vector<int> b;
	b.insert(b.begin(), a.begin(), a.begin() + 1);
	b.insert(b.end(), a.begin() + 1, a.begin() + 4);
	b.insert(b.end(), a.begin() + 4, a.end());
	assert(std::equal(b.begin(), b.end(), a.begin()));
}

static void operator_cmp(void)
{
	ft::vector<int> a;
	ft::vector<int> b;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	assert(a == b);
	b.push_back(4);
	assert(a != b);
	a.push_back(0);
	assert(a < b);
	assert(a <= b);
	assert(b > a);
	assert(b >= a);
}

void vector_tests(void)
{
	constructor_default();
	constructor_fill();
	constructor_range();
	constructor_copy();
	operator_equal();
	vector_iterator();
	vector_riterator();
	resize();
	at();
	back_nd_front();
	assign();
	push_back();
	pop_back();
	erase();
	swap();
	insert();
	operator_cmp();
	(void)dump_vector;
}
