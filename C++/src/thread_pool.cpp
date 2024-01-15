#include "thread_pool.hpp"

#include <iostream> // cout
#include <algorithm> // min

namespace concurrency
{

ThreadPool::ThreadPool(size_t a_threads, size_t a_tasks)
: m_tasks{a_tasks}
{
    add(a_threads);
}

ThreadPool::~ThreadPool()
{
    shutdown();
    remove(threads());
}

size_t ThreadPool::threads() const
{
    return m_threads.size();
}


void ThreadPool::shutdown()
{
    m_stop = true;
    while(true)
    {
        if(m_tasks.empty())
        {
            m_tasks.cancel();
            return;
        }
    }
}

void ThreadPool::shutdown_immediate()
{
    m_stop = true;
    m_tasks.cancel();
    m_tasks.clear();
}

void ThreadPool::remove(size_t a_amount)
{
    m_to_remove = std::min(a_amount, threads());
    if(not m_stop)
    {
        for (size_t i = 0; i < a_amount; ++i)
        {
            submit([](){});
        }
    }
    while(m_to_remove)
    {
        for(auto itr = m_threads.begin(); itr != m_threads.end();)
        {
            if((*itr).joinable())
            {
                (*itr).join();
                itr = m_threads.erase(itr);
                --m_to_remove;
                if(m_to_remove == 0)
                {
                    return;
                }
            }
            else
            {
                ++itr;
            }
        }
    }
}

void ThreadPool::add(size_t a_amount)
{
    for (size_t i = 0; i < a_amount; ++i)
    {
        m_threads.emplace_back([this]{
            while(not (m_stop and m_tasks.empty()))
            {
                std::function<void()> task;
                // if(m_stop and m_tasks.empty())
                // {
                //     return;
                // }
                try
                {
                    this->m_tasks.dequeue(task);
                }
                catch(std::runtime_error const& e)
                {
                    std::cout << e.what() << '\n';
                    return;
                }
                task();
                if(this->m_to_remove)
                {
                    return;
                }
            }    
        });
    }
}

} // namespace concurrency
