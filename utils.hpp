#ifndef UTILS_HPP
#define UTILS_HPP

// Advent of Code 2018
// utils.hpp 

#include <algorithm>
#include <functional>

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

// Split a line into std::string tokens
// See: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Split a line into tokens, we may have multiple possible delimiters
// Inspired by: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
template <typename FWIter, typename Func>
std::vector<std::string> split(FWIter first, FWIter last, Func is_delim)
{
    auto pos = first;
    auto lst = FWIter();
    auto tokens = std::vector<std::string>();
    while (pos!=last)
    {
        lst = std::find_if(pos,last,is_delim);
        auto token = std::string(pos,lst);
        tokens.push_back(token);
        pos = std::find_if(lst,last,std::not1(is_delim));
    }
    return tokens;
}

#endif