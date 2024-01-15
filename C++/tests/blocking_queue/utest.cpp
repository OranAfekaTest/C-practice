#include "mu_test.h"
#include "blocking_queue.hpp"

#include <iostream> //cout
#include <thread>
#include <vector>

void producer_func(ds::BlockingQueue<int>& a_queue, size_t a_amount) {
	for (size_t i = 0; i < a_amount; ++i) {
		a_queue.enqueue(i+1);
		std::cout << "enqueue " << i+1 << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void consumer_func(ds::BlockingQueue<int>& a_queue, size_t a_amount) {
	int value;
	for (size_t i = 0; i < a_amount; ++i) {
		a_queue.dequeue(value);
        std::cout << "dequeue " << value << '\n';
	}
}

BEGIN_TEST(test_empty)
	
	ds::BlockingQueue<int> queue{};
	ASSERT_THAT(queue.empty());

END_TEST

BEGIN_TEST(test_size)
	ds::BlockingQueue<int> queue{};
	producer_func(queue, 5);
	ASSERT_EQUAL(queue.size(), 5);
END_TEST

BEGIN_TEST(test_full)
	ds::BlockingQueue<int> queue{};
	producer_func(queue, 10);
	ASSERT_THAT(queue.full());
END_TEST

BEGIN_TEST(test_producer_consumer)
	ds::BlockingQueue<int> queue(5);

	std::vector<std::thread> producer_threads;
	for (size_t i = 0; i < 5; ++i) {
		producer_threads.emplace_back(producer_func, std::ref(queue), 10);
	}
	
	std::vector<std::thread> consumer_threads;
	for (size_t i = 0; i < 5; ++i) {
		consumer_threads.emplace_back(consumer_func, std::ref(queue), 10);
	}

	for (auto& thread: producer_threads) {
		thread.join();
	}

	for (auto& thread: consumer_threads) {
		thread.join();
	}
	
	ASSERT_PASS();
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

	TEST(test_empty)
	TEST(test_size)
	TEST(test_full)
	TEST(test_producer_consumer)

END_SUITE
