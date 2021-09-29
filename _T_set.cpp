#include <cassert>
#include <string>
#include <set>
#include "vector.hpp"
#include "set.hpp"
#include "pair.hpp"

static void default_constructor(void)
{
	ft::set<int> a;

	assert(a.size() == 0);
}

static void iterator_constructor(void)
{
	ft::vector<int> ref;
	ref.push_back(2);
	ref.push_back(4);
	ref.push_back(6);
	ft::set<int> a(ref.begin(), ref.end());
	assert(*(a.find(2)) == 2);
	assert(*(a.find(4)) == 4);
	assert(*(a.find(6)) == 6);
}

static void copy_constructor(void)
{
	ft::vector<int> ref;
	ref.push_back(2);
	ref.push_back(4);
	ref.push_back(6);
	ft::set<int> a(ref.begin(), ref.end());
	ft::set<int> b(a);
	assert(*(b.find(2)) == 2);
	assert(*(b.find(4)) == 4);
	assert(*(b.find(6)) == 6);
}

static void capacity(void)
{
	std::set<int> a;
	ft::set<int> b;

	assert(b.empty());
	assert(a.empty() == b.empty());
}

static void set_iterator(void)
{
	ft::set<int> a;
	int i = 10;
	a.insert(10);
	a.insert(20);
	a.insert(30);
	ft::set<int>::iterator it = a.begin();
	while (it != a.end())
	{
		assert(i == *it++);
		i += 10;
	}
	i -= 10;
	while (it != a.begin())
	{
		assert(i == *--it);
		i -= 10;
	}
	ft::set<int>::reverse_iterator rt = a.rbegin();
	i = 30;
	while (rt != a.rend())
	{
		assert(i == *rt++);
		i -= 10;
	}
	i += 10;
	while (rt != a.rbegin())
	{
		assert(i == *--rt);
		i += 10;
	}

}

static void set_insert(void)
{
	ft::set<std::string> a;
	ft::set<std::string> b;
	a.insert("aurelien");
	a.insert("bonjour");
	a.insert("aventiin");
	assert(a.count("aurelien") == 1);
	assert(a.count("bonjour") == 1);
	assert(a.count("aventiin") == 1);
}

static void set_erase(void)
{
	ft::set<std::string> a;
	a.insert("aurelien");
	a.insert("bonjour");
	a.insert("aventiin");
	a.erase("aurelien");
	a.erase("bonjour");
	a.erase("aventiin");
	assert(a.find("aurelien") == a.end());
	assert(a.find("bonjour") == a.end());
	assert(a.find("aventiin") == a.end());
	assert(a.size() == 0);
}

static void set_swap(void)
{
	ft::set<std::string> a;
	a.insert("aurelien");
	a.insert("bonjour");
	a.insert("aventiin");
	ft::set<std::string> b;
	b.swap(a);
	assert(a.find("aurelien") == a.end());
	assert(a.find("bonjour") == a.end());
	assert(a.find("aventiin") == a.end());
	assert(b.count("aurelien") == 1);
	assert(b.count("bonjour") == 1);
	assert(b.count("aventiin") == 1);
}

static void set_find(void)
{
	ft::set<std::string> a;
	a.insert("aurelien");
	a.insert("bonjour");
	a.insert("aventiin");
	assert(a.find("PNL") == a.end());
	assert(*(a.find("aurelien")) == "aurelien");
	assert(*(a.find("bonjour")) == "bonjour");
	assert(*(a.find("aventiin")) == "aventiin");
}

void set_tests(void)
{
	default_constructor();
	iterator_constructor();
	copy_constructor();
	capacity();
	set_iterator();
	set_insert();
	set_erase();
	set_swap();
	set_find();
}
