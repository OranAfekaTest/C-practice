#include "mu_test.h"
#include "queue_stack.hpp"

#include <climits> // INT_MIN_MAX

using namespace ds;

BEGIN_TEST(test_add_remove)
	
    QueueStack s;
    int a = 42;
	s.add(a);
    a = s.remove();
	ASSERT_EQUAL(a, 42);
	
END_TEST

BEGIN_TEST(test_size)
	int n[] = {0, 2, 42, INT_MAX, -2, -42, -INT_MAX, INT_MIN};
    QueueStack s;

	for(size_t i = 0; i < sizeof(n)/sizeof(*n); ++i){
		s.add(n[i]);
		ASSERT_EQUAL(s.get_size(), i + 1);
	}

END_TEST

BEGIN_TEST(test_double_free)
	
    QueueStack s;
	s.add(4);

	{
		QueueStack test_free = s;
		int four = test_free.remove();
		ASSERT_EQUAL(four, 4);
	}
	
	ASSERT_THAT(s.peek() == 4);

END_TEST

TEST_SUITE(queue_stack tests)
	
	TEST(test_add_remove)
	TEST(test_size)
	TEST(test_double_free)

END_SUITE
