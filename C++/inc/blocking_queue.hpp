#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <cstddef> // size_t
#include <deque> // deque
#include <mutex> // mutex
#include <condition_variable> // condition variable

namespace ds
{
template<typename T>
class BlockingQueue : private std::deque<T>
{
public:
    BlockingQueue(size_t a_cap = 10);
    ~BlockingQueue();
    void enqueue(T const& a_item);
    void dequeue(T& a_item);
    size_t size() const;   // how many elenets currently inside.       size()  <= cap
    bool full() const;
    bool empty() const; 
    void cancel();
    void clear();

private:
    size_t m_cap;
    std::mutex m_mtx;
    std::condition_variable m_enqueue_cv;
    std::condition_variable m_dequeue_cv;
    bool m_canceled = false;
};
} // namespace ds
#include "inl/blocking_queue.hxx"
#endif // BLOCKING_QUEUE_HPP

