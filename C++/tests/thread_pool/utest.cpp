#include "mu_test.h"
#include "thread_pool.hpp"

#include <iostream> //cout
#include <thread>
#include <vector>

using namespace std::chrono_literals; // this_thread::sleep miliseconds

void first_func() 
{
	std::cout << "first_func" << '\n';
}

void second_func() 
{
        std::cout << "second_func" << '\n';
}

void short_wait() 
{
	std::cout << "short_wait" << '\n';
	std::this_thread::sleep_for(10ms);
}

void long_wait() 
{
	std::cout << "long_wait" << '\n';
	std::this_thread::sleep_for(2000ms);
}

BEGIN_TEST(test_constructing_threadpools)
	concurrency::ThreadPool tp_empty{};
	concurrency::ThreadPool tp_single_arg{4};
	concurrency::ThreadPool tp_full{4, 1000};

	// tp_empty.shutdown();
	// tp_single_arg.shutdown();
	// tp_full.shutdown();

	const auto processor_count = std::thread::hardware_concurrency();

	ASSERT_EQUAL(tp_empty.threads(), processor_count - 1);
	ASSERT_EQUAL(tp_single_arg.threads(), 4);
	ASSERT_EQUAL(tp_full.threads(), 4);
	
END_TEST

BEGIN_TEST(test_submit_two_functions)
	concurrency::ThreadPool tp{};
	
	tp.submit(first_func);
	tp.submit(second_func);

	ASSERT_PASS();
	
END_TEST

BEGIN_TEST(test_submit_one_thousend_functions)
	concurrency::ThreadPool tp{4, 1000};
	
	for (size_t i = 0; i < 1000; ++i)
	{
		if(i % 2 == 0)
		{
			tp.submit(first_func);
		}
		else
		{
			tp.submit(second_func);
		}
	}
	ASSERT_PASS();
	
END_TEST

BEGIN_TEST(test_shutdown)
	concurrency::ThreadPool tp{4, 1000};
	
	for (size_t i = 0; i < 100; ++i)
	{
		tp.submit(short_wait);
	}

	tp.shutdown();
	tp.submit(first_func);
	try
	{
		tp.submit(first_func);
	}
	catch(std::runtime_error const& e)
	{
		TRACE(e.what());
		ASSERT_PASS();
	}
	ASSERT_FAIL("should throw runtime error");
	
END_TEST

BEGIN_TEST(shutdown_immediate)
	concurrency::ThreadPool tp{4, 1000};
	
	for (size_t i = 0; i < 100; ++i)
	{
		tp.submit(short_wait);
	}

	tp.shutdown_immediate();

	ASSERT_PASS();
	
END_TEST

BEGIN_TEST(test_remove_two_threads)
	concurrency::ThreadPool tp{};
	
	tp.submit(first_func);
	tp.submit(second_func);
	tp.remove(2);
	size_t num_of_threads = tp.threads();
	ASSERT_EQUAL(num_of_threads, 5);
	
END_TEST

BEGIN_TEST(test_add_two_threads)
	concurrency::ThreadPool tp{};
	
	tp.submit(first_func);
	tp.submit(second_func);
	tp.add(2);
	size_t num_of_threads = tp.threads();
	ASSERT_EQUAL(num_of_threads, 9);
	
END_TEST

TEST_SUITE([don`t thread on me])

	TEST(test_constructing_threadpools)
	TEST(test_submit_two_functions)
	TEST(test_submit_one_thousend_functions)
	TEST(test_shutdown)
	TEST(shutdown_immediate)
	TEST(test_add_two_threads)
	TEST(test_remove_two_threads)

END_SUITE
