#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstddef> // size_t

/**
 * @brief represent a fraction
 *
 */
 
namespace algebra
{
class Rational {
public:
    Rational(int a_numerator, int a_denomerator);
    Rational(int a_numerator);
    Rational(void);

    Rational& print();
    Rational const& print() const;
    double value() const;
    Rational& inverse();
    Rational& reduce();
    Rational& operator+=(Rational const& a_toAdd);
    Rational& operator-=(Rational const& a_toASub);
    Rational& operator*=(Rational const& a_toMul);
    Rational& operator/=(Rational const& a_toDiv);
    bool operator<(Rational const& a_rVal) const;
    bool operator>(Rational const& a_rVal) const;
    bool operator<=(Rational const& a_rVal) const;
    bool operator>=(Rational const& a_rVal) const;
    bool operator==(Rational const& a_rVal) const;
    bool operator!=(Rational const& a_rVal) const;
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    void swap(Rational& a_other);
    
private:
    int m_numerator;
    int m_denomerator;
};

bool equal_to(Rational a_a, Rational a_b);
bool not_equal_to(Rational a_a, Rational a_b);
double sumd(Rational const* a_rational_array, size_t a_size);
Rational sum(Rational const* a_rational_array, size_t a_size);
Rational operator+(Rational const& a_lVal, Rational const& a_rVal);
Rational operator-(Rational const& a_lVal, Rational const& a_rVal);
Rational operator*(Rational const& a_lVal, Rational const& a_rVal);
Rational operator/(Rational const& a_lVal, Rational const& a_rVal);
} // algebra

namespace util_func
{
void swap(int& a, int& b);
int gcd(int a_a, int a_b);
} // util_func

#endif // RATIONAL_HPP
