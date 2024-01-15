#include "../inc/stack.hpp"

#include <cassert> // assert
#include <iostream> // cout
#include <cstring> // memcpy

#define DEFAULT_CAPACITY 10

using namespace std;
namespace ds
{
Stack::Stack() :
m_stack(new int[DEFAULT_CAPACITY]),
m_top(0),
m_capacity(DEFAULT_CAPACITY)
{
}

Stack::Stack(size_t a_capacity) :
m_stack(new int[a_capacity]),
m_top(0),
m_capacity(a_capacity)
{
    assert(a_capacity);
}

Stack::Stack(Stack const& a_other) :
m_stack(new int[a_other.m_capacity]),
m_top(a_other.m_top),
m_capacity(a_other.m_capacity)
{
    memcpy(m_stack, a_other.m_stack, a_other.get_size() * sizeof *m_stack);
}

Stack::~Stack()
{
    delete[](m_stack);
}

Stack& Stack::operator+=(Stack& a_other)
{
    /*
    Stack holder(a_other.get_size());
    drain(a_other, holder);
    drain(holder, *this);
    if(!holder.is_empty())
    {
        drain(holder, a_other);
    }
    */
    if(this != &a_other and a_other.get_size() <= m_capacity - m_top)
    {
        memcpy(m_stack + m_top, a_other.m_stack, a_other.get_size() * sizeof *a_other.m_stack);
        m_top += a_other.m_top;
        a_other.m_top = 0;
    }
    return *this;
}

Stack& Stack::operator=(Stack const& a_other)
{
    if(this != &a_other)
    {
        if(m_capacity != a_other.m_capacity)
        {
            delete[](m_stack);
            m_stack = new int[a_other.m_capacity];
            m_capacity = a_other.m_capacity;
        }
        memcpy(m_stack, a_other.m_stack, a_other.get_size() * sizeof *m_stack);
        m_top = a_other.m_top;
    }

    return *this;
}

Stack& Stack::push(int a_item)
{
    assert(!is_full());
    m_stack[m_top++] = a_item;
    return *this;
}

int Stack::pop()
{
    assert(!is_empty());
    return m_stack[--m_top];
}

int Stack::peek() const
{
    assert(!is_empty());
    return m_stack[m_top - 1];
}

Stack const& Stack::print() const
{
    cout << "[ ";
    for(size_t i = 0; i < m_top; ++i)
    {
        cout << m_stack[i];
        if(i < m_top - 1)
        {
            cout << ", ";
        }
    }
    cout << " ]";
    return *this;
}

size_t Stack::get_size() const
{
    return m_top;
}

size_t Stack::get_capacity() const
{
    return m_capacity;
}


bool Stack::is_empty() const
{
    return !m_top;
}

bool Stack::is_full() const
{
    return m_top == m_capacity;
}


void drain(Stack& a_a, Stack& a_b)
{
    while(!a_a.is_empty() and !a_b.is_full())
    {
        a_b.push(a_a.pop());
    }
}

Stack& Stack::operator=(Stack&& a_other)
{
    if(this != &a_other)
    {
        m_stack = a_other.m_stack;
        m_capacity = a_other.m_capacity;
        m_top = a_other.m_top;
        a_other.m_stack = nullptr;
        a_other.m_top = 0;
        a_other.m_capacity = 0;
    }
    return *this;
}

Stack::Stack(Stack&& a_other)
: m_stack(a_other.m_stack)
, m_top(a_other.m_top)
, m_capacity(a_other.m_capacity)
{
    a_other.m_stack = nullptr;
    a_other.m_top = 0;
    a_other.m_capacity = 0;
}
} //ds