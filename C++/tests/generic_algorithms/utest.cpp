#include "generic_algorithms.hpp"
#include <cassert>


class Cat
{
public:
    Cat()
    : m_str("Meow"){}
    Cat(string a_str)
    : m_str(a_str){}
    
    friend ostream& operator<< (ostream& a_os, Cat const& a_cat)
    {
        return a_os << a_cat.m_str;
    }

private:
    string m_str;
};


int main()
{
    // 1.implement  functions to print any container
    vector<int> e;
    vector<int> o(1, 6);
    vector<int> v(3, 4);
    cout << e;  // print exactly: [ ]
    cout << o;  // print exactly: [ 6]
    cout << v;  // print exactly: [ 4, 4, 4 ]
    list<Cat> lst;
    lst.push_back(Cat("pixel"));
    lst.push_back(Cat("quark"));
    cout << lst; // prin exactly: [ pixel, quark ]

    // 2.implement a function to print a subrange from a container.
    vector<int> v(3, 14);
    print(v.begin(), v.end());

    // 3.implement a function that will compute the multiplication of all items in a container.
    vector<int> v(3, 10);
    cout << mul(v.begin(), v.end()); // 1000

    // 4.implement a generic function that can apply a binary operation over the elements in the vector:
    vector<int> v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(10);
    v.push_back(20);
    cout << foldit(v.begin(), v.end(), add);  // 40
    // as if executed  add(add(v[0], v[1]), v[2])
    cout << foldit(v.begin(), v.end(), mul);  // 4200

    // 5.implement a generic function that can merge two  sorted ranges into a third one (sorted):
    vector<int> v; // assume: 1, 4, 7, 9, 12, 13, 15
    vector<int> w; // assume: 2, 3, 5 10, 13, 18, 19
    vector<int> r(14);
    merge(v, w, r);
    cout << r;
    // [1,2,3,4,57,9,10,12,13,1315,18,19 ]

    // 6. implement a generic function that replaces each element in a vector with the nearest element on right that is greater than it otherwise leave as is
    vector<int> v;
    // fill with:   1, 5, 2, 1, 4, 3, 7, 2
    replace_with_left_bigger(v);
    print(v);
    // prints  [ 5, 7, 4, 4, 4, 5, 7, 7, 2 ]
}
