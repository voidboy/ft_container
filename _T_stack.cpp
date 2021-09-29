#include <cassert>
#include "stack.hpp"

static void default_constructor(void)
{
	ft::stack<int> s;
	assert(s.size() == 0);
	assert(s.empty());
}

static void stack_pop(void)
{
	ft::stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.pop();
	assert(s.top() == 2);
	s.pop();
	assert(s.top() == 1);
	assert(s.size() == 1);
	/* undefined behaviour when empty */
}

static void stack_push(void)
{
	ft::stack<int> s;

	s.push(1);
	assert(s.top() == 1);
	s.push(2);
	assert(s.top() == 2);
	s.push(3);
	assert(s.top() == 3);
	assert(s.size() == 3);
}

void stack_tests(void)
{
	default_constructor();
	stack_pop();
	stack_push();
}
