#ifndef THREAD_POOL_HXX
#define THREAD_POOL_HXX

#include "../thread_pool.hpp"

namespace concurrency
{

static const auto processor_count = std::thread::hardware_concurrency();

ThreadPool::ThreadPool(size_t a_threads = processor_count - 1, size_t a_tasks = 10)
: m_threads{a_threads}
, m_tasks{a_tasks}
{
    for (size_t i = 0; i < a_threads; ++i)
    {
        m_threads.emplace_back([this]{
            while(true)
            {
                std::function<void()> task;
                this->m_tasks.dequeue(task);
                if(this->m_tasks.empty())
                {
                    return;
                }
                task();
            }    
        });
    }
}

ThreadPool::~ThreadPool()
{
    for(std::thread& thread : m_threads)
    {
        thread.join();
    }
}

size_t ThreadPool::threads() const
{
    return m_threads.size();
}

} // namespace concurrency
#endif // THREAD_POOL_HXX