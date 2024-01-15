#include <cassert> // assert
#include <cstddef> //size_t

namespace ds
{
template<typename T>
class Node
{
public:
    Node() = default;
    Node(T const& a_data, Node const* a_next, Node const* a_prev);
    ~Node() = default;

    Node* get_next() const;
	Node* get_prev() const;
    T get_data() const;
    Node& set_next(Node* a_next);
	Node& set_prev(Node* a_prev);
    Node& set_data(T const& a_data);

private:
	T m_data;
	Node* m_next;
	Node* m_prev;
};

template<typename T>
Node<T>::Node(T const& a_data, Node const* a_next, Node const* a_prev)
: m_data(a_data)
, m_next(a_next)
, m_prev(a_prev)
{
}

template<typename T>
Node<T>* Node<T>::get_next() const
{
    return m_next;
}

template<typename T>
Node<T>* Node<T>::get_prev() const
{
    return m_prev;
}

template<typename T>
T Node<T>::get_data() const
{
    return m_data;
}

template<typename T>
Node<T>& Node<T>::set_next(Node* a_next)
{
    assert(a_next);
    if(a_next)
    {
        m_next = a_next;
    }
    return *this;
}

template<typename T>
Node<T>& Node<T>::set_prev(Node* a_prev)
{
    assert(a_prev);
    if(a_prev)
    {
        m_prev = a_prev;
    }
    return *this;
}

template<typename T>
Node<T>& Node<T>::set_data(T const& a_data)
{
    m_data = a_data;
    return *this;
}

template<typename T>
class List
{
public:
    List();
    ~List();

    List& push_head(T const& a_data);
    T pop_head();
    List& append(T const& a_data);
    T pop_tail();
    
    size_t get_size() const;
    List& find_and_insert_after(T const& a_after, T const& a_data);
    List& clear();
    List& swap(List& a_other);
    List& foreach(void (*pf)(T& a_corrent, T& a_pc), T& a_ctx);
    List& remove(T const& a_item);
    bool contains(T const& a_item);
    friend bool operator<(List const& a_lVal, List const& a_rAl);
    friend bool operator==(List const& a_lVal, List const& a_rAl);
    friend bool operator!=(List const& a_lVal, List const& a_rAl);
    
private:
	Node<T> m_head;
	Node<T> m_tail;
    size_t m_size;

    Node<T>* find(T const& a_data);
    void insert_after(Node<T>* m_node, T const& a_data);
    void insert_before(Node<T>* m_node, T const& a_data);
    T remove_node(Node<T>* m_node);
};

template<typename T>
List<T>::List()
: m_head(T{}, &m_tail, nullptr)
, m_tail(T{}, nullptr, &m_head)
, m_size(0)
{
}

template<typename T>
List<T>& List<T>::push_head(T const& a_data)
{
    insert_after(&m_head, a_data);
    return *this;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
T List<T>::pop_head()
{
    /*
    T result = m_head.get_next()->get_data();
    Node<T>* node_to_pop = m_head.get_next();
    m_head.set_next(m_head.get_next()->get_next());
    m_head.get_next()->set_prev(&m_head);
    delete node_to_pop;
    --m_size;
    return result;
    */
    return remove_node(m_head.get_next());
}

template<typename T>
List<T>& List<T>::append(T const& a_data)
{
    insert_before(&m_tail, a_data);
    return *this;
}

template<typename T>
T List<T>::pop_tail()
{
    /*
    T result = m_tail.get_prev()->get_data();
    Node<T>* node_to_pop = m_tail.get_prev();
    m_tail.set_prev(node_to_pop->get_prev());
    m_tail.get_prev()->set_next(&m_tail);
    delete node_to_pop;
    --m_size;
    return result;
    */
    return remove_node(m_tail.get_prev());
}

template<typename T>
size_t List<T>::get_size() const
{
    return this->m_size;
}

template<typename T>
List<T>& List<T>::find_and_insert_after(T const& a_after, T const& a_data)
{
    Node<T>* node = find(a_after);
    if(node)
    {
        insert_after(node, a_data);
    }
    return *this;
}

template<typename T>
Node<T>* List<T>::find(T const& a_data)
{
    Node<T>* current = m_head.get_next();
    for(size_t i = 0; i < get_size(); ++i)
    {
        if(current->get_data() == a_data)
        {
            return current;
        }
        current = current->get_next();
    }
    return NULL;
}

template<typename T>
void List<T>::insert_after(Node<T>* a_node, T const& a_data)
{
    Node<T>* new_node = new Node<T>(a_data, a_node->get_next(), a_node);
    a_node->get_next()->set_prev(new_node);
    a_node->set_next(new_node);
    ++m_size;
}

template<typename T>
void List<T>::insert_before(Node<T>* a_node, T const& a_data)
{
    Node<T>* new_node = new Node<T>(a_data, a_node, a_node->get_prev());
    a_node->get_prev()->set_next(new_node);
    a_node->set_prev(new_node);
    ++m_size;
}

template<typename T>
T List<T>::remove_node(Node<T>* m_node)
{
    assert(m_node == &m_head or m_node == &m_tail);

    Node<T>* next_node = m_node->get_next();
    Node<T>* prev_node = m_node->get_prev();
    prev_node->set_next(next_node);
    next_node->set_prev(prev_node);
    T data = m_node->get_data();
    delete m_node;
    --m_size;
    return data;
}

template<typename T>
List<T>& List<T>::clear()
{
    Node<T>* current = m_head.get_next();
    while(current != &m_tail)
    {
        Node<T>* next = current->get_next();
        delete current;
        current = next;
    }
    m_size = 0;
    return *this;
}

template<typename T>
List<T>& List<T>::swap(List& a_other)
{
    m_head.get_next()->set_prev(&a_other.m_head);
    m_tail.get_prev()->set_next(&a_other.m_tail);
    a_other.m_head.get_next()->set_prev(&m_head);
    a_other.m_tail.get_prev()->set_next(&m_tail);

    Node<T>* first = m_head.get_next();
    m_head.set_next(a_other.m_head->get_next());
    a_other.m_head->set_next(first);

    Node<T>* last = m_tail.get_prev();
    m_tail.set_prev(a_other.m_tail.get_prev());
    a_other.m_tail.set_prev(last);
}

template<typename T>
List<T>& List<T>::remove(T const& a_item)
{
    Node<T>* node = find(a_item);
    if(node)
    {
        remove_node(node);
    }
    return *this;
}

template<typename T>
bool List<T>::contains(T const& a_item)
{
    if(find(a_item))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
bool operator<(List<T> const& a_lVal, List<T> const& a_rAl)
{
    Node<T>* lVal_node = a_lVal.m_head.get_next();
    Node<T>* rVal_node = a_rVal.m_head.get_next();

    while(lVal_node != a_lVal.m_tail and rVal_node != a_rVal.m_tail)
    {
        if(lVal_node->get_data() != rVal_node->get_data())
        {
            if(lVal_node->get_data() < rVal_node->get_data())
            {
                return true;
            }
            return false;
        }
        lVal_node = lVal_node->m_head.get_next();
        rVal_node = rVal_node->m_head.get_next();
    }

    if(lVal_node == a_lVal.m_tail)
    {
        return false;
    }
    return true;
}

template<typename T>
bool operator==(List<T> const& a_lVal, List<T> const& a_rAl)
{
    if(a_lVal.m_size != a_rAl.m_size)
    {
        return false;
    }

    Node<T>* lVal_node = a_lVal.m_head.get_next();
    Node<T>* rVal_node = a_rVal.m_head.get_next();

    while(lVal_node != a_lVal.m_tail)
    {
        if(lVal_node->get_data() != rVal_node->get_data())
        {
            return false;
        }
        lVal_node = lVal_node->m_head.get_next();
        rVal_node = rVal_node->m_head.get_next();
    }

    return true;
}

template<typename T>
bool operator!=(List<T> const& a_lVal, List<T> const& a_rAl)
{
    return(!(a_lVal == a_rAl));
}

template<typename T>
List<T>& List<T>::foreach(void (*pf)(T& a_corrent, T& a_pc), T& a_ctx)
{
    Node<T>* current_node = m_head.get_next();
    while(current_node != &m_tail)
    {
        pf(current_node->get_data(), a_ctx);
        current_node = current_node->get_next();
    }
    return *this;
}
} //ds