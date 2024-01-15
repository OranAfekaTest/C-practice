#ifndef __GENERIC_ALGORITHMS_HPP__
#define __GENERIC_ALGORITHMS_HPP__

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class Iterator>
void print_container(Iterator a_begin, Iterator a_end, ostream& a_os)
{
     a_os << "[";
    for (Iterator itr = a_begin; itr != a_end; ++itr)
    {
        if(itr != a_begin)
        {
            a_os << ",";
        }
        a_os << " " << *itr;
    }
    a_os << " ]" << endl;
}

template <class Container, typename = typename Container::value_type>
ostream& operator<<(ostream& a_os, const Container& a_con) 
{
    print_container(a_con.begin(), a_con.end(), a_os);
    return a_os;
}

template<typename T, typename Iterator>
T  mul( Iterator a_begin,  Iterator a_end)
{
    if (a_begin == a_end) {
		return T{};
    }

	T result = *a_begin;
	++a_begin;
    while( a_begin != a_end ) {
        result *= *a_begin;
        ++a_begin;
    }
    return result;
}

template<typename T, typename Iterator>
T foldit(Iterator a_begin,  Iterator a_end, T (*action)(T, T))
{
    T result = *a_begin;
    ++a_begin;

    while( a_begin != a_end ) {
        result = action(result, *a_begin);
        ++a_begin;
    }

    return result;
}

template<typename Container, typename Iterator>
void merge(const Container& a_first, const Container& a_second, Container& result) 
{
    Iterator first_itr = begin(a_first);
    Iterator second_itr = begin(a_second);

    while(first_itr != a_first.end() or second_itr != a_second.end())
    {
        if(*first_itr < *second_itr)
        {
            result.push_back(*first_itr);
        } else {
            result.push_back(*second_itr);
        }
        
        ++first_itr;
        ++second_itr;
    }

    if(first_itr != a_first.end())
    {
        result.push_back(*first_itr);
        ++first_itr;
    }
    if(second_itr != a_second.end())
    {
        result.push_back(*second_itr);
        ++second_itr;
    }
}

template<typename Container, typename Iterator>
void replace_with_left_bigger(Container& a_container)
{
    for (Iterator itr = begin(a_container); itr != end(a_container); ++itr)
    {
        Iterator runner = ++itr;
        while(runner != end(a_container))
        {
            if(*itr < *runner)
            {
                *itr = *runner;
                break;
            }
        }
    }
}

#endif // __GENERIC_ALGORITHMS_HPP__