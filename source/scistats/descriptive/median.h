//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MEDIAN_H
#define SCISTATS_MEDIAN_H

// C++
#include <algorithm>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>

namespace scistats {
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    median_inplace(Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        size_t s = std::distance(begin, end);
        const bool is_odd = s & 1U;
        Iterator middle = begin + s / 2;
        std::nth_element(begin, middle, end);
        if (is_odd) {
            return static_cast<return_type>(*middle);
        } else {
            Iterator lower_middle = std::max_element(begin, middle);
            return static_cast<return_type>(*middle + *lower_middle) / 2.0;
        }
    }

    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    median_copy(Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        std::vector<std::decay_t<value_type>> copy(begin, end);
        return median_inplace(copy.begin(), copy.end());
    }

    /// Sequential median value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    median(scistats::execution::sequenced_policy, Iterator begin,
           Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        using pointer_type = typename std::iterator_traits<Iterator>::pointer;
        if constexpr (std::is_const_v<std::remove_pointer_t<pointer_type>>) {
            return median_copy(begin, end);
        } else {
            return median_inplace(begin, end);
        }
    }

    /// Parallel median value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    median(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        return median(scistats::execution::seq, begin, end);
    }

    template <class Iterator> auto median(Iterator begin, Iterator end) {
        return median(scistats::execution::seq, begin, end);
    }

    template <class Range>
    auto median(scistats::execution::sequenced_policy e, const Range &c) {
        return median(e, c.begin(), c.end());
    }

    template <class Range>
    auto median(scistats::execution::parallel_policy e, const Range &c) {
        return median(e, c.begin(), c.end());
    }

    template <class Range> auto median(const Range &c) {
        return median(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MEDIAN_H
