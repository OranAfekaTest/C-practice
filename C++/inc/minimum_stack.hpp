#ifndef __MINMSTACK_HPP__
#define __MINMSTACK_HPP__

#include <cstddef> // size_t

namespace ds
{
class MinStack
{
public:
    MinStack();
    MinStack(size_t a_capacity);
    MinStack(MinStack const& a_other);
    ~MinStack();

    MinStack& push(int a_item);
    int pop();
    int peek() const;
    int get_min() const;
    MinStack const& print() const;
    size_t get_size() const;
    size_t get_capacity() const;
    bool is_empty() const;
    bool is_full() const;
    
    MinStack& operator+=(MinStack& a_other);
    MinStack& operator=(MinStack const& a_other);

private:
    int* m_minstack;
    size_t m_top;
    size_t m_capacity;
    int m_min;
};

void drain(MinStack& a_a, MinStack& a_b);
} // ds

#endif /*__MINMSTACK_HPP__*/