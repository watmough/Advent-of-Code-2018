#ifndef UTILS_HPP
#define UTILS_HPP

// Advent of Code 2018
// utils.hpp 

// Count non-matching values over two ranges of iterators
// See: https://en.cppreference.com/w/cpp/algorithm/count
template<class InputIt>
typename std::iterator_traits<InputIt>::difference_type
    count_mismatches(InputIt first, InputIt last, InputIt first2)
{
    typename std::iterator_traits<InputIt>::difference_type ret = 0;
    for (; first != last; ++first,++first2) {
        if (*first!=*first2) {
            ret++;
        }
    }
    return ret;
}

// Handy algorithm to run a function over all pairs of a range
// See: https://youtu.be/h4Jl1fk3MkQ?t=1420 [Marshall Clow - STL Algorithms]
template <typename FWIter, typename Func>
void for_all_pairs(FWIter first, FWIter last, Func f)
{
    if (first!=last) {
        FWIter trailer = first; 
        ++first;
        for (; first!=last; ++first,++trailer)
            for (FWIter it=first; it!=last; ++it)
                f(*trailer, *it);
    }
}

#endif