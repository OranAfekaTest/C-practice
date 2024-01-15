#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include "blocking_queue.hpp"
#include <vector> // vector
#include <thread> // thread
#include <functional> // function
#include <atomic> // atomic_ulong

namespace concurrency
{

static const auto processor_count = std::thread::hardware_concurrency();

class ThreadPool
{
public:
   
    ThreadPool(size_t a_threads = processor_count - 1, size_t a_tasks = 10);
    ~ThreadPool();

    template <typename Task>
    void submit(Task a_task)
    {
        if(not m_stop)
        {
            m_tasks.enqueue(a_task);
        }
        else
        {
            throw std::runtime_error("can't submit new tasks after shutdown");
        }
    } 

    size_t threads() const
;
    void shutdown(); // close the pool, no more tasks will be accepted, finish executing all tasks already submitted before
                // what should we do with the threads?

    // // Phase 3
    void add(size_t a_amount = 1); // add more 2 worker threads

    // // Phase 4
    void remove(size_t a_amount);  // remove 2 threads rfom the pool
    void shutdown_immediate();  // shutdown the pool promptly, don'ta ccept new tasks, just finish all tasks that already have
    //                         // started to be executed by worker threads. leave any task that is in the queue but has not started yet.

private:
    std::vector<std::thread> m_threads;
    ds::BlockingQueue<std::function<void()>> m_tasks;
    std::atomic_bool m_stop = false;
    std::atomic_ulong m_to_remove = 0;
};
} // namespace concurrency

#endif // THREAD_POOL_HPP