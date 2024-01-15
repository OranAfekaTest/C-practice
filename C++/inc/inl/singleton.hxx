#ifndef SINGLETON_HXX
#define SINGLETON_HXX

#include "singleton.hpp"

template <typename T>
T* Singleton<T>::self_pointer = nullptr;

template <typename T>
T* Singleton<T>::get_instance()
{
    if(self_pointer == nullptr)
    {
        Singleton<T>::self_pointer = new T();
        std::atexit([](){delete Singleton<T>::self_pointer;});
    }

    return Singleton<T>::self_pointer;
}

#endif // SINGLETON_HXX