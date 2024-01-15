#ifndef ALGORITHMS_HXX
#define ALGORITHMS_HXX

#include "algorithms.hpp"
#include<iterator> // iterator_traits
#include<type_traits> // enable_if

template<typename Itr>
void reverse_forawrd_itr(Itr a_itr_begin, Itr a_itr_end);

template<typename Itr>
void reverse_bidir_itr(Itr a_itr_begin, Itr a_itr_end);

template<typename Itr>
void reverse(Itr a_itr_begin, Itr a_itr_end)
{
    using category = typename std::iterator_traits<Itr>::iterator_category;
    if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
    {
        reverse_bidir_itr(a_itr_begin, a_itr_end);
    }
    else if constexpr (std::is_same_v<category, std::forward_iterator_tag>)
    {
        reverse_forawrd_itr(a_itr_begin, a_itr_end);
    }
}

template<typename Itr>
void swap_itrs(Itr a_first, Itr a_second)
{
    typename std::iterator_traits<Itr>::value_type tmp = *a_first;
    *a_first = *a_second;
    *a_second = tmp;
}

template<typename Itr>
void reverse_bidir_itr(Itr a_itr_begin, Itr a_itr_end)
{
    typename std::iterator_traits<Itr>::difference_type n = std::distance(a_itr_begin, a_itr_end);
        for (--n; n > 0; n -= 2)
        {
            swap_itrs(a_itr_begin, --a_itr_end);
            ++a_itr_begin;
        }
}

template<typename Itr>
void reverse_forawrd_itr(Itr a_itr_begin, Itr a_itr_end)
{
    using diff_t = typename std::iterator_traits<Itr>::difference_type;
    diff_t n = std::distance(a_itr_begin, a_itr_end);
    while(a_itr_begin != a_itr_end)
    {
        Itr runner = a_itr_begin;
        for (diff_t i = 0; i < n - 1; ++i)
        {
            ++runner;
        }
        swap_itrs(a_itr_begin, runner);
        n -= 2;
        ++a_itr_begin;
    }   
    
}


#endif // ALGORITHMS_HPP