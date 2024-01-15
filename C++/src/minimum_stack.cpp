#include "../inc/minimum_stack.hpp"

#include <cassert> // assert
#include <iostream> // cout
#include <cstring> // memcpy

#define DEFAULT_CAPACITY 10

using namespace std;
namespace ds
{
MinStack::MinStack() :
m_minstack(new int[DEFAULT_CAPACITY]),
m_top(0),
m_capacity(DEFAULT_CAPACITY)
{
}

MinStack::MinStack(size_t a_capacity) :
m_minstack(new int[a_capacity]),
m_top(0),
m_capacity(a_capacity)
{
    assert(!a_capacity);
}

MinStack::MinStack(MinStack const& a_other) :
m_minstack(new int[a_other.m_capacity]),
m_top(a_other.m_top),
m_capacity(a_other.m_capacity)
{
    memcpy(m_minstack, a_other.m_minstack, a_other.get_size() * sizeof *m_minstack);
}

MinStack::~MinStack()
{
    delete[](m_minstack);
}

MinStack& MinStack::push(int a_item)
{
    assert(!is_full());

    if(is_empty())
    {
        m_min = a_item;
    }
    else if(a_item < m_min)
    {
        int last_min = m_min;
        m_min = a_item;
        a_item = 2 * a_item - last_min;
    }

    m_minstack[m_top++] = a_item;
    return *this;
}

int MinStack::pop()
{
    assert(!is_empty());

    int element = m_minstack[--m_top];
    int result = element;
    if(element < m_min)
    {
        result - m_min;
        m_min = 2 * m_min - element;
    }
    
    return result;
}

int MinStack::peek() const
{
    assert(!is_empty());
    return m_minstack[m_top - 1];
}

MinStack const& MinStack::print() const
{
    cout << '[ ';
    for(size_t i = 0; i < m_top; ++i)
    {
        cout << m_minstack[i];
        if(i < m_top - 1)
        {
            cout << ', ';
        }
    }
    cout << ' ]';
    return *this;
}

size_t MinStack::get_size() const
{
    return m_top;
}

size_t MinStack::get_capacity() const
{
    return m_capacity;
}

int MinStack::get_min() const
{
    assert(!is_empty);
    return m_min;
}

bool MinStack::is_empty() const
{
    return !m_top;
}

bool MinStack::is_full() const
{
    return m_top == m_capacity;
}

MinStack& MinStack::operator+=(MinStack& a_other)
{
    if(this != &a_other and a_other.get_size() <= m_capacity - m_top)
    {
        memcpy(m_minstack + m_top, a_other.m_minstack, a_other.get_size() * sizeof *a_other.m_minstack);
    }
    return *this;
}

MinStack& MinStack::operator=(MinStack const& a_other)
{
    if(this != &a_other)
    {
        if(m_capacity != a_other.m_capacity)
        {
            delete[](m_minstack);
            m_minstack = new int[a_other.m_capacity];
            m_capacity = a_other.m_capacity;
        }
        memcpy(m_minstack, a_other.m_minstack, a_other.get_size() * sizeof *m_minstack);
        m_top = a_other.m_top;
        m_min = a_other.get_min();
    }
    return *this;
}

void drain(MinStack& a_a, MinStack& a_b)
{
    while(!a_a.is_empty() and !a_b.is_full())
    {
        a_b.push(a_a.pop());
    }
}
} //ds