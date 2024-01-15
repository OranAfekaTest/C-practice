#include "mu_test.h"
#include "minimum_stack.hpp"

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

TEST_SUITE(stack tests)
	
	TEST(test_push_pop)
	TEST(test_size)

END_SUITE
