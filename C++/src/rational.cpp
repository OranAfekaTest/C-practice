#include "rational.hpp"

#include <cassert> //input check
#include <cstdio> // print

namespace algebra
{
Rational::Rational(int a_numerator, int a_denomerator)
{
    assert(a_denomerator != 0);

    if(a_denomerator < 0)
    {
        m_numerator = -a_numerator;
        m_denomerator = -a_denomerator;
    }
    else
    {
        m_numerator = a_numerator;
        m_denomerator = a_denomerator;
    }
}

Rational::Rational(int a_numerator)
{
    m_numerator = a_numerator;
    m_denomerator = 1;
}

Rational::Rational(void)
{
    m_numerator = 0;
    m_denomerator = 1;
}

Rational& Rational::inverse()
{
    Rational holder(m_denomerator, m_numerator);
    this->swap(holder);

    return *this;
}

void Rational::swap(Rational& a_other)
{
    util_func::swap(m_numerator, a_other.m_numerator);
    util_func::swap(m_denomerator, a_other.m_denomerator);
}

Rational& Rational::operator+=(Rational const& a_toAdd)
{
    Rational chageable = a_toAdd;
    //make common denomerator
    this->m_numerator *= a_toAdd.m_denomerator;
    chageable.m_numerator *= this->m_denomerator;
    this->m_denomerator *= a_toAdd.m_denomerator;
    //a_toAdd.m_denomerator = this->m_denomerator;
    //add
    this->m_numerator += chageable.m_numerator;
    this->reduce();
    return *this;
}

Rational& Rational::operator-=(Rational const& a_toSub)
{
    Rational chageable = a_toSub;
    chageable.m_numerator *= -1;
    *this += chageable;
    return *this;
}

Rational& Rational::operator*=(Rational const& a_toMul)
{
    this->m_numerator *= a_toMul.m_numerator;
    this->m_denomerator *= a_toMul.m_denomerator;
    this->reduce();
    return *this;
}

Rational& Rational::operator/=(Rational const& a_toDiv)
{
    Rational chageable = a_toDiv;
    //this->m_numerator *= a_toDiv.m_denomerator;
    //this->m_denomerator *= a_toDiv.m_numerator;
    *this *= chageable.inverse();
    return *this;
}

Rational operator+(Rational const& a_lVal, Rational const& a_rVal)
{
    Rational result = a_lVal;
    result += a_rVal;
    return result;
}

Rational operator-(Rational const& a_lVal, Rational const& a_rVal)
{
    Rational result = a_lVal;
    result -= a_rVal;
    return result;
}

Rational operator*(Rational const& a_lVal, Rational const& a_rVal)
{
    Rational result = a_lVal;
    result *= a_rVal;
    return result;
}

Rational operator/(Rational const& a_lVal, Rational const& a_rVal)
{
    Rational result = a_lVal;
    result /= a_rVal;
    return result;
}

Rational& Rational::reduce()
{
    int _gcd = util_func::gcd(m_numerator, m_denomerator);
    
    m_numerator /= _gcd;
    m_denomerator /= _gcd;

    return *this;
}

Rational& Rational::print()
{
    printf("%d/%d", m_numerator, m_denomerator);
    return *this;
}

Rational const& Rational::print() const
{
    printf("%d/%d", m_numerator, m_denomerator);
    return *this;
}

double Rational::value() const
{
    //BEENDONE: dragons be gone
    return m_numerator/(double)m_denomerator;
}

bool Rational::operator<(Rational const& a_rVal) const
{
    int this_numerator = this->m_numerator * a_rVal.m_denomerator;
    int cmp_numerator = a_rVal.m_numerator * this->m_denomerator;
    return this_numerator < cmp_numerator;
}

bool Rational::operator>(Rational const& a_rVal) const
{
    return a_rVal < *this;
}

bool Rational::operator<=(Rational const& a_rVal) const
{
    return *this < a_rVal or *this == a_rVal;
}

bool Rational::operator>=(Rational const& a_rVal) const
{
    return *this > a_rVal or *this == a_rVal;
}

bool Rational::operator==(Rational const& a_rVal) const
{
    return !(*this < a_rVal) and !(a_rVal < *this);
}

bool Rational::operator!=(Rational const& a_rVal) const
{
    return !(*this == a_rVal);
}

Rational& Rational::operator++()
{
    m_numerator += m_denomerator;
    return *this;
}

Rational Rational::operator++(int)
{
    Rational original = *this;
    ++(*this);
    return original;
}

Rational& Rational::operator--()
{
    m_numerator -= m_denomerator;
    return *this;
}

Rational Rational::operator--(int)
{
    Rational original = *this;
    --(*this);
    return original;
}

bool equal_to(Rational a_a, Rational a_b)
{
    if(a_a < a_b || a_b < a_a)
    {
        return false;
    }
    
    return true;
}

bool not_equal_to(Rational a_a, Rational a_b)
{
    return !equal_to(a_a, a_b);
}

double sumd(Rational const* a_rational_array, size_t a_size)
{
    return sum(a_rational_array, a_size).value();
}

Rational sum(Rational const* a_rational_array, size_t a_size)
{
    Rational result;
    if(!a_rational_array || !a_size)
    {
        return 0;
    }
    
    for(size_t i = 0; i < a_size; ++i)
    {
        result += a_rational_array[i];
    }

    return result;
}

} // algebra

namespace util_func
{
void swap(int& a_a, int& a_b)
{
    int swapper = a_a;
    a_b = a_b;
    a_b = swapper;
}

int gcd(int a_a, int a_b)
{
    if(a_a == 0)
    {
        return a_b;
    }
        
    if(a_b == 0)
    {
        return a_a;
    }
        
    if(a_a < a_b)
    {
        return gcd(a_a, a_b % a_a);
    }
    else
    {
        return gcd(a_b, a_a % a_b);
    }
}
} // util_func
    
        