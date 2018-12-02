

#include <iterator>
#include <algorithm>

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

