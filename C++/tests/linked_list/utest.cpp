#include "mu_test.h"
#include "linked_list.hpp"

#include <climits> // INT_MIN_MAX

using namespace ds;

BEGIN_TEST(test_push_pop_head)
	List <size_t> lst;
	
	for(size_t i = 0; i < 10; ++i)
	{
		lst.push_head(i + 1);
	}

	for(size_t i = 10; 0 < i; --i)
	{
		size_t cmp_val = lst.pop_head();
		ASSERT_EQUAL(cmp_val , i);
	}

END_TEST

BEGIN_TEST(test_push_pop_tail)
	List <size_t> lst;
	
	for(size_t i = 0; i < 10; ++i)
	{
		lst.append(i + 1);
	}

	for(size_t i = 10; 0 < i; --i)
	{
		size_t cmp_val = lst.pop_tail();
		ASSERT_EQUAL(cmp_val , i);
	}

END_TEST

BEGIN_TEST(test_size)
	List <size_t> lst;
	size_t cmp_val;
	for(size_t i = 0; i < 10; ++i)
	{
		lst.append(i + 1);
		cmp_val = lst.get_size();
		ASSERT_EQUAL(cmp_val , i + 1);
	}

	for(size_t i = 10; 0 < i; --i)
	{
		cmp_val = lst.pop_tail();
		ASSERT_EQUAL(cmp_val , i);
		ASSERT_THAT(lst.get_size() == i -1);
	}

END_TEST

BEGIN_TEST(test_insert_after)
	List <size_t> lst;
	size_t cmp_val;
	size_t after_val = 5;

	for(size_t i = 0; i < 10; ++i)
	{
		lst.append(i + 1);
		cmp_val = lst.get_size();
		ASSERT_EQUAL(cmp_val , i + 1);
	}

	lst.find_and_insert_after(after_val, after_val * after_val);

	for(size_t i = 10; after_val < i; --i)
	{
		cmp_val = lst.pop_tail();
		ASSERT_EQUAL(cmp_val , i);
		ASSERT_THAT(lst.get_size() == i);
	}

	cmp_val = lst.pop_tail();
	ASSERT_EQUAL(cmp_val , after_val * after_val);

END_TEST

BEGIN_TEST(test_swap)
	List <size_t> lst;
	List <size_t> to_swap;

	for(size_t i = 0; i < 10; ++i)
	{
		lst.append(i + 1);
	}
	List <size_t> identical_lst = lst;
	ASSERT_THAT(identical_lst == lst);

	for(size_t i = 10; after_val < i; --i)
	{
		to_swap.append(i);
	}
	List <size_t> identical_to_swap = to_swap;
	ASSERT_THAT(identical_to_swap == to_swap);

	lst.swap(to_swap);
	ASSERT_THAT(identical_to_swap == lst);
	ASSERT_THAT(identical_lst == to_swap);

END_TEST

BEGIN_TEST(test_clear)
	List <size_t> lst;
	size_t cmp_val;

	for(size_t i = 0; i < 10; ++i)
	{
		lst.append(i + 1);
		cmp_val = lst.get_size();
		ASSERT_EQUAL(cmp_val , i + 1);
	}

	lst.clear();

	cmp_val = lst.get_size();
	ASSERT_EQUAL(cmp_val , 0);

END_TEST

TEST_SUITE(stack tests)
	
	TEST(test_push_pop_head)
	TEST(test_push_pop_tail)
	TEST(test_size)
	TEST(test_insert_after)
	TEST(test_clear)

END_SUITE
