#ifndef SMART_PTR_HXX
#define SMART_PTR_HXX

#include "smart_ptr.hpp"

template <typename T>
SmartPointer<T>::SmartPointer(T* p) 
: m_ptr{p} 
{}

template <typename T>
SmartPointer<T>::~SmartPointer() 
{ 
    delete m_ptr; 
}

template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer<T>&& a_other) noexcept
: m_ptr{a_other.m_ptr}
{
    a_other.m_ptr = nullptr;
}

template <typename T>
template <typename U>
SmartPointer<T>::SmartPointer(SmartPointer<U>&& a_other) noexcept
: m_ptr{a_other.m_ptr}
{
    a_other.m_ptr = nullptr;
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>&& a_other) noexcept
{
    if(this != &a_other)
    {
        delete m_ptr;
        m_ptr = a_other.m_ptr;
        a_other.m_ptr = nullptr;
    }
    return *this;
}

template <typename T>
template <typename U>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<U>&& a_other) noexcept
{
    delete m_ptr;
    m_ptr = a_other.m_ptr;
    a_other.m_ptr = nullptr;
}

template <typename T>
T* SmartPointer<T>::get() const 
{ 
    return m_ptr;
}

template <typename T>
T* SmartPointer<T>::operator->() const noexcept
{ 
    return m_ptr; 
}

// template <typename T>
// T const* SmartPointer<T>::operator->() const 
// { 
//     return ptr; 
// }

// template <typename T>
// T* SmartPointer<T>::operator->()  
// { 
//     return ptr; 
// }

template <typename T>
T& SmartPointer<T>::operator*() const
{ 
    return *m_ptr; 
}

// template <typename T>
// T const& SmartPointer<T>::operator*() const 
// { 
//     return *m_ptr; 
// }

// template <typename T>
// T& SmartPointer<T>::operator*()  
// { 
//     return *m_ptr; 
// }

template <typename T>
SmartPointer<T>::operator bool() const noexcept
{ 
    return m_ptr != nullptr; 
}

#endif // SMART_PTR_HXX