#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cstddef> // size_t

namespace ds
{
class Stack
{
public:
    Stack();
    Stack(size_t a_capacity);
    Stack(Stack const& a_other);
    Stack(Stack&& a_other);
    ~Stack();

    Stack& push(int a_item);
    int pop();
    int peek() const;
    Stack const& print() const;
    size_t get_size() const;
    size_t get_capacity() const;
    bool is_empty() const;
    bool is_full() const;
    
    Stack& operator+=(Stack& a_other);
    Stack& operator=(Stack const& a_other);
    Stack& operator=(Stack&& a_other);



private:
    int* m_stack;
    size_t m_top;
    size_t m_capacity;
};

void drain(Stack& a_a, Stack& a_b);
} // ds

#endif /*__STACK_HPP__*/