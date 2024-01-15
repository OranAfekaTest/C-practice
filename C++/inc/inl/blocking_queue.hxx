#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include "../blocking_queue.hpp"

namespace ds
{
template<typename T>
BlockingQueue<T>::BlockingQueue(size_t a_cap)
: std::deque<T>{}
, m_cap{a_cap}
{}

template<typename T>
BlockingQueue<T>::~BlockingQueue()
{
    cancel();
}

template<typename T>
void BlockingQueue<T>::enqueue(T const& a_item)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    while(full() and not m_canceled) 
    {
        m_enqueue_cv.wait(lock);
    }
    if(m_canceled)
    {
        throw std::runtime_error("queue was canceled");
    }
    // m_enqueue_cv.wait(lock, [this]{
    //     return this->full();
    //     });

    std::deque<T>::push_back(a_item);
    m_dequeue_cv.notify_one();
}

template<typename T>
void BlockingQueue<T>::dequeue(T& a_item)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    while(empty() and not m_canceled) 
    {
        m_dequeue_cv.wait(lock);
    }
    if(m_canceled)
    {
        throw std::runtime_error("queue was canceled");
    }
    // m_dequeue_cv.wait(lock, [this]{
    //     return this->empty();
    //     });

    a_item = std::move(std::deque<T>::front());
    std::deque<T>::pop_front();
    m_enqueue_cv.notify_one();
}

template<typename T>
size_t BlockingQueue<T>::size() const
{
    return std::deque<T>::size();
}

template<typename T>
bool BlockingQueue<T>::full() const
{
    return size() >= m_cap;
}

template<typename T>
bool BlockingQueue<T>::empty() const
{
    return std::deque<T>::empty();
}

template<typename T>
void BlockingQueue<T>::clear()
{
    std::deque<T>::clear();
}

template<typename T>
void BlockingQueue<T>::cancel()
{
    m_canceled = true;
    m_enqueue_cv.notify_all();
    m_dequeue_cv.notify_all();
}
} // namespace ds

#endif // BLOCKING_QUEUE_HXX