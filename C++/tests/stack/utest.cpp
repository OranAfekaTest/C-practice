#include "mu_test.h"
#include "stack.hpp"

#include <climits> // INT_MIN_MAX

using namespace ds;

BEGIN_TEST(test_push_pop)
	
    Stack s;
    int a = 42;
	s.push(a);
    a = s.pop();
	ASSERT_EQUAL(a, 42);
	
END_TEST

BEGIN_TEST(test_size)
	int n[] = {0, 2, 42, INT_MAX, -2, -42, -INT_MAX, INT_MIN};
    Stack s;

	for(size_t i = 0; i < sizeof(n)/sizeof(*n); ++i){
		s.push(n[i]);
		ASSERT_EQUAL(s.get_size(), i + 1);
	}

END_TEST

BEGIN_TEST(test_double_free)
	
    Stack s;
	s.push(4);

	{
		Stack test_free = s;
		int four = test_free.pop();
		ASSERT_EQUAL(four, 4);
	}
	
	ASSERT_THAT(s.peek() == 4);

END_TEST

BEGIN_TEST(test_plus_equal_operator)
	int n[] = {0, 2, 42, INT_MAX, -2, -42, -INT_MAX, INT_MIN};
    Stack a(100);
	Stack b;
	b.push(1);
	b.push(2);
	b.push(3);
	b.push(4);
	size_t a_size = 0;
	size_t b_size = b.get_size();
	
	for(size_t i = 0; i < sizeof(n)/sizeof(*n); ++i){
		a.push(n[i]);
		a_size = a.get_size();
		ASSERT_EQUAL(a_size, i + 1);
	}
	
	a += b;
	ASSERT_EQUAL(a.get_size(), a_size + b_size);
	ASSERT_EQUAL(b.get_size(), 0);

	for(int i = b_size; 0 < i; --i){
		int val = a.pop();
		ASSERT_EQUAL(val, i);
	}

	for(size_t i = sizeof(n)/sizeof(*n); 0 < i; --i){
		int stack_val = a.pop();
		int array_val = n[i - 1];
		ASSERT_EQUAL(stack_val, array_val);
	}
	ASSERT_EQUAL(a.get_size(), 0);

END_TEST

BEGIN_TEST(test_copy_ctor)
	
    Stack a(100);
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	
	Stack b = a;

	ASSERT_EQUAL(b.get_capacity(), 100);
	ASSERT_EQUAL(b.pop(), 4);
	ASSERT_EQUAL(b.pop(), 3);
	ASSERT_EQUAL(b.pop(), 2);
	ASSERT_EQUAL(b.pop(), 1);
	ASSERT_THAT(b.is_empty());

END_TEST

BEGIN_TEST(test_assignment)
	
    Stack a(100);
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	
	Stack b;
	b = a;

	ASSERT_EQUAL(b.get_capacity(), 100);
	ASSERT_EQUAL(b.pop(), 4);
	ASSERT_EQUAL(b.pop(), 3);
	ASSERT_EQUAL(b.pop(), 2);
	ASSERT_EQUAL(b.pop(), 1);
	ASSERT_THAT(b.is_empty());

END_TEST

TEST_SUITE(stack tests)
	
	TEST(test_push_pop)
	TEST(test_size)
	TEST(test_double_free)
	TEST(test_plus_equal_operator)
	TEST(test_copy_ctor)
	TEST(test_assignment)

END_SUITE
