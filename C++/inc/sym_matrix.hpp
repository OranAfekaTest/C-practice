#include <iostream> // ostream operator
#include <cassert> //assert
#include <cstring> // memcpy
#include <iomanip> // setw for pretty print padding

static size_t index(size_t a_x, size_t a_y);
static size_t sum_until(size_t a_to_sum);

template<typename T>
class SymMatrix
{
public:
    SymMatrix(size_t a_dim);
    SymMatrix(SymMatrix const& a_other);
    template<typename U>
    SymMatrix(SymMatrix<U> const& a_other);
    ~SymMatrix();
    SymMatrix& operator=(SymMatrix const& a_other);

    T& operator()(size_t a_x, size_t a_y);

    SymMatrix& operator+=(SymMatrix const& a_other);
    template<typename U>
    friend SymMatrix<U> operator+ /*<T>*/(SymMatrix<U> const& a_lVal, SymMatrix<U> const& a_rVal);
    
    template<typename U>
    SymMatrix& operator*=(U m_scalar);
    template<typename U, typename Y>
    friend SymMatrix<U> operator* (SymMatrix<U> const& a_mat, Y m_scalar);
    template<typename U, typename Y>
    friend SymMatrix<U> operator* (Y m_scalar, SymMatrix<U> const& a_mat);

    template<typename U>
    friend std::ostream& operator<< /*<T>*/(std::ostream& out, SymMatrix<U> const& a_mat);
    
    template<typename U>
    friend class SymMatrix;

private:
    size_t m_dim;
    size_t m_size;
    T* m_data;
};


size_t index(size_t a_x, size_t a_y)
{
    size_t bigger = a_x, smaller = a_y;
    if(a_x < a_y)
    {
        bigger = a_y;
        smaller = a_x;
    }
    return (bigger * (bigger + 1)) / 2 + smaller;
}

size_t sum_until(size_t a_to_sum)
{
    size_t sum = 0;
    for(size_t i = 0; i <= a_to_sum; ++i)
    {
        sum += i;
    }
    return sum;
}

template<typename T>
SymMatrix<T>::SymMatrix(size_t a_dim)
: m_dim(a_dim)
, m_size(sum_until(m_dim))
, m_data(new T[m_size]{})
{
}

template<typename T>
SymMatrix<T>::SymMatrix(SymMatrix const& a_other)
: m_dim(a_other.m_dim)
, m_size(sum_until(m_dim))
, m_data(new T[m_size])
{
    memcpy(m_data, a_other.m_data, m_size);
}


template<typename T>
template<typename U>
SymMatrix<T>::SymMatrix(SymMatrix<U> const& a_other)
: m_dim(a_other.m_dim)
, m_size(sum_until(m_dim))
, m_data(new T[m_size])
{
    memcpy(m_data, a_other.m_data, m_size);
}

template<typename T>
SymMatrix<T>::~SymMatrix()
{
    delete[] m_data;
}


template<typename T>
SymMatrix<T>& SymMatrix<T>::operator+=(SymMatrix<T> const& a_other)
{
    if(m_dim == a_other.m_dim)
    {
        for(size_t i = 0; i < m_size; ++i)
        {
            m_data[i] += a_other.m_data[i];
        }
    }
    return *this;
}

template<typename T>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix<T> const& a_other)
{
    if(m_dim == a_other.m_dim)
    {
        memcpy(m_data, a_other.m_data, m_size);
    }
    return *this;
}

template<typename T>
T& SymMatrix<T>::operator()(size_t a_x, size_t a_y)
{
    assert(a_x < m_dim and a_y < m_dim);
    return m_data[index(a_x, a_y)];
}

template<typename T>
SymMatrix<T> operator+(SymMatrix<T> const& a_lVal, SymMatrix<T> const& a_rVal)
{
    assert(a_lVal.m_dim == a_rVal.m_dim);
    SymMatrix<T> result(a_lVal.m_dim);
    if(a_lVal.m_dim == a_rVal.m_dim)
    {
        result = a_lVal;
        result += a_rVal;
    }
    return result;
}

template<typename T>
template<typename U>
SymMatrix<T>& SymMatrix<T>::operator*=(U m_scalar)
{
    for(size_t i = 0; i < m_size; ++i)
    {
        m_data[i] *= m_scalar;
    }

    return *this;
}

template<typename T, typename U>
SymMatrix<T> operator*(SymMatrix<T> const& a_mat, U m_scalar)
{
    SymMatrix<T> result(a_mat);

    result *= m_scalar;

    return result;
}

template<typename T, typename U>
SymMatrix<T> operator*(U m_scalar, SymMatrix<T> const& a_mat)
{
    return a_mat * m_scalar;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, SymMatrix<T> const& a_mat)
{
    for(size_t i = 0; i < a_mat.m_dim; ++i)
    {
        for(size_t j = 0; j < a_mat.m_dim; ++j)
        {
            out << std::setw(4) << a_mat.m_data[index(i, j)];
            if(j < a_mat.m_dim - 1)
            {
                out << ", ";
            }
        }
        out << "\n\n";
    }
    
    out << std::endl;
    return out;
}
