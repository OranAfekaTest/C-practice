#include "mu_test.h"

#include "ball.hpp"
#include "brick.hpp"
#include "paddle.hpp"

BEGIN_TEST(_equality_on_integers)
	int a = 42;
	size_t s = 42;

	ASSERT_EQUAL(a, 42);
	ASSERT_EQUAL(s, 42);

	int n = 42;
	long m = 42;

	ASSERT_EQUAL(n, m);
END_TEST

BEGIN_TEST(add_operations)
	int n = 42;
	int r = n++;

	ASSERT_EQUAL(n, 43);
	ASSERT_EQUAL(r, n-1);
END_TEST

BEGIN_TEST(empty_class_is_not_empty)
	class K{};

	ASSERT_THAT(sizeof(K) != 0);
	ASSERT_EQUAL(sizeof(K), 1);
END_TEST

BEGIN_TEST(default_string_is_empty)
	std::string s;

	ASSERT_THAT(s.size() == 0);
	ASSERT_EQUAL_STR(s.c_str(), "");
	ASSERT_THAT(s == "");
END_TEST

BEGIN_TEST(string_equality)
	const char* cstr = "abc";
	std::string s(cstr);
	ASSERT_EQUAL(s, cstr);

	std::string t;

	ASSERT_NOT_EQUAL(s, t);
	t = s;
	ASSERT_EQUAL(s, t);
END_TEST

BEGIN_TEST(tracers)
	TRACER << "hello world" << '\n';
	short mayo = 42;
	TRACE(mayo);

	double burger = 3.14;
	TRACER << "short " << mayo << " and a double " << burger << '\n';
	ASSERT_EQUAL(mayo, 42);
END_TEST

BEGIN_TEST(test_should_fail)
	ASSERT_FAIL("fail on demand");
END_TEST

BEGIN_TEST(test_should_pass)
	ASSERT_PASS();
END_TEST


BEGIN_TEST(test_with_no_assert_should_fail)

END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(_equality_on_integers)
	TEST(add_operations)

	TEST(empty_class_is_not_empty)
	TEST(default_string_is_empty)
	TEST(string_equality)

	TEST(tracers)

	TEST(test_should_fail)
	TEST(test_should_pass)

	TEST(test_with_no_assert_should_fail)
END_SUITE
