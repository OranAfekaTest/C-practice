#include "queue_stack.hpp"

namespace ds
{
QueueStack::QueueStack() :
m_push_stack(),
m_pop_stack()
{
}

QueueStack::QueueStack(size_t a_capacity) :
m_push_stack(a_capacity),
m_pop_stack(a_capacity)
{
}

QueueStack::QueueStack(QueueStack const& a_other) :
m_push_stack(a_other.m_push_stack),
m_pop_stack(a_other.m_pop_stack)
{
}

QueueStack& QueueStack::add(int a_item)
{
    /*
    if(m_push_stack.is_empty())
    {
        drain(m_pop_stack, m_push_stack);
    }
    */
    m_push_stack.push(a_item);
    return *this;
}

int QueueStack::remove()
{
    if(m_pop_stack.is_empty())
    {
        drain(m_push_stack, m_pop_stack);
    }

    return m_pop_stack.pop();
}

size_t QueueStack::get_size() const
{
    if(m_pop_stack.is_empty())
    {
        return m_push_stack.get_size();
    }
    else
    {
        return m_pop_stack.get_size();
    }
}

size_t QueueStack::get_capacity() const
{
    return m_push_stack.get_capacity();
}

bool QueueStack::is_empty() const
{
    return m_push_stack.is_empty() and m_push_stack.is_empty();
}

int QueueStack::peek()
{
    if(m_pop_stack.is_empty())
    {
        drain(m_push_stack, m_pop_stack);
    }

    return m_pop_stack.peek();
}
} // ds