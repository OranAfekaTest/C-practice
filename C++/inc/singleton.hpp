#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton
{
public:
    virtual ~Singleton()  = default;
    Singleton(Singleton const& other) = delete;
    Singleton& operator=(Singleton const& other) = delete;

    static T* get_instance();

protected:
    Singleton() = default;

private:
    static T* self_pointer;
};

#include "inl/singleton.hxx"
#endif // SINGLETON_HPP