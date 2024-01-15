#include "mu_test.h"
#include "algorithms.hpp"

#include <vector>
#include <list>
#include <forward_list>

int arr[] = {5, 4, 3, 2, 1};

BEGIN_TEST(test_vecor)
	std::vector<int> vector;
	for (int i = 4; i >= 0; --i)
	{
		vector.push_back(arr[i]);
	}
	reverse(vector.begin(), vector.end());

	for (int i = 0; i < 5; ++i)
	{
		ASSERT_EQUAL(vector[i], arr[i]);
	}

END_TEST

BEGIN_TEST(test_list)
	std::list<std::string> list;
	for (int i = 4; i >= 0; --i)
	{
		list.push_back(std::to_string(arr[i]));
	}
	reverse(list.begin(), list.end());

	for (int i = 0; i < 5; ++i)
	{
		ASSERT_EQUAL(list.front(), std::to_string(arr[i]));
		list.pop_front();
	}
	
END_TEST

BEGIN_TEST(test_forward_list)
	std::forward_list<int> forward_list;
	for (int i = 0; i < 5; ++i)
	{
		forward_list.push_front(arr[i]);

	}

	reverse(forward_list.begin(), forward_list.end());

	for (int i = 0; i < 5; ++i)
	{
		ASSERT_EQUAL(forward_list.front(), arr[i]);
		forward_list.pop_front();
	}

END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

	TEST(test_vecor)
	TEST(test_list)
	TEST(test_forward_list)

END_SUITE
