#ifndef SMART_PTR_HPP
#define SMART_PTR_HPP

template <typename T>
class SmartPointer
{
public:
    explicit SmartPointer(T* p = nullptr);
    ~SmartPointer();
    SmartPointer(SmartPointer&& other) noexcept;
    template <typename U>
    SmartPointer(SmartPointer<U>&& other) noexcept;
    SmartPointer& operator=(SmartPointer&& other) noexcept;
    template <typename U>
    SmartPointer<T>& operator=(SmartPointer<U>&& other) noexcept;
    SmartPointer& operator=(SmartPointer const& other) = delete;
    T* get() const;

    T* operator->() const noexcept;
    // T const* operator->() const;
    // T* operator->();

    T& operator*() const;
    // T const& operator*() const;
    // T& operator*();

    explicit operator bool() const noexcept;


private:
    T* m_ptr;
};

#include "inl/smart_ptr.hxx"
#endif // SMART_PTR_HPP