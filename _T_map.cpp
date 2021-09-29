#include <cassert>
#include <string>
#include <map>
#include "vector.hpp"
#include "map.hpp"
#include "pair.hpp"

static void default_constructor(void)
{
	ft::map<int, int> a;

	assert(a.size() == 0);
}

static void iterator_constructor(void)
{
	ft::vector<ft::pair<int, int> > ref;
	ref.push_back(ft::pair<int, int>(1, 2));
	ref.push_back(ft::pair<int, int>(3, 4));
	ref.push_back(ft::pair<int, int>(5, 6));
	ft::map<int, int> a(ref.begin(), ref.end());
	assert(a[1] == 2);
	assert(a[3] == 4);
	assert(a[5] == 6);
}

static void copy_constructor(void)
{
	ft::vector<ft::pair<int, int> > ref;
	ref.push_back(ft::pair<int, int>(1, 2));
	ref.push_back(ft::pair<int, int>(3, 4));
	ref.push_back(ft::pair<int, int>(5, 6));
	ft::map<int, int> a(ref.begin(), ref.end());
	ft::map<int, int> b(a);
	assert(b[1] == 2);
	assert(b[3] == 4);
	assert(b[5] == 6);
}

static void capacity(void)
{
	std::map<int, int> a;
	ft::map<int, int> b;

	assert(b.empty());
	assert(a.empty() == b.empty());
}

static void map_iterator(void)
{
	ft::map<int, int> a;
	int i = 10;
	a[10] = 10;
	a[20] = 20;
	a[30] = 30;
	ft::map<int, int>::iterator it = a.begin();
	while (it != a.end())
	{
		assert(i == (*it++).first);
		i += 10;
	}
	i -= 10;
	while (it != a.begin())
	{
		assert(i == (*--it).first);
		i -= 10;
	}
	ft::map<int, int>::reverse_iterator rt = a.rbegin();
	i = 30;
	while (rt != a.rend())
	{
		assert(i == (*rt++).first);
		i -= 10;
	}
	i += 10;
	while (rt != a.rbegin())
	{
		assert(i == (*--rt).first);
		i += 10;
	}

}

static void map_insert_test(void)
{
	const ft::pair<const std::string, int> orel("aurelien", 3);
	ft::vector<ft::pair<std::string, int> > pool;
	pool.push_back(ft::pair<std::string, int>("aurelien", 1));
	pool.push_back(ft::pair<std::string, int>("bonjour", 2));
	pool.push_back(ft::pair<std::string, int>("aventiin", 3));
	ft::map<std::string, int> a;
	ft::map<std::string, int> b;
	a.insert(ft::pair<std::string, int>("aurelien", 1));
	a.insert(ft::pair<std::string, int>("bonjour", 2));
	a.insert(ft::pair<std::string, int>("aventiin", 3));
	assert(a["aurelien"] == 1);
	assert(a["bonjour"] == 2);
	assert(a["aventiin"] == 3);
	b.insert(a.begin(), a.end());
	assert(b["aurelien"] == 1);
	assert(b["bonjour"] == 2);
	assert(b["aventiin"] == 3);
	a.insert(pool.begin(), pool.end());

}

static void map_erase(void)
{
	ft::map<std::string, int> a;
	a.insert(ft::pair<std::string, int>("aurelien", 1));
	a.insert(ft::pair<std::string, int>("bonjour", 2));
	a.insert(ft::pair<std::string, int>("aventiin", 3));
	a.erase("aurelien");
	a.erase(a.begin(), a.end());
	assert(a.find("aurelien") == a.end());
	assert(a.find("bonjour") == a.end());
	assert(a.find("aventiin") == a.end());
	assert(a.size() == 0);
}

static void map_swap(void)
{
	ft::map<std::string, int> a;
	a.insert(ft::pair<std::string, int>("aurelien", 1));
	a.insert(ft::pair<std::string, int>("bonjour", 2));
	a.insert(ft::pair<std::string, int>("aventiin", 3));
	ft::map<std::string, int> b;
	b.swap(a);
	assert(a.find("aurelien") == a.end());
	assert(a.find("bonjour") == a.end());
	assert(a.find("aventiin") == a.end());
	assert(b["aurelien"] == 1);
	assert(b["bonjour"] == 2);
	assert(b["aventiin"] == 3);
}

static void map_find(void)
{
	ft::map<std::string, int> a;
	a.insert(ft::pair<std::string, int>("aurelien", 1));
	a.insert(ft::pair<std::string, int>("bonjour", 2));
	a.insert(ft::pair<std::string, int>("aventiin", 3));
	assert(a.find("PNL") == a.end());
	assert((*(a.find("aurelien"))).second == 1);
	assert((*(a.find("bonjour"))).second == 2);
	assert((*(a.find("aventiin"))).second == 3);
}

void map_tests(void)
{
	default_constructor();
	iterator_constructor();
	copy_constructor();
	capacity();
	map_iterator();
	map_insert_test();
	map_erase();
	map_swap();
	map_find();
}
