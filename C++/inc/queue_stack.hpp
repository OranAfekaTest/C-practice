#include "stack.hpp"

namespace ds
{
class QueueStack
{
public:
    QueueStack();
    QueueStack(size_t a_capacity);
    QueueStack(QueueStack const& a_other);

    QueueStack& add(int a_item);
    int remove();
    int peek();
    size_t get_size() const;
    size_t get_capacity() const;
    bool is_empty() const;

private:
    Stack m_push_stack;
    Stack m_pop_stack;
};
} // sd