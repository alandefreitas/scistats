//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MIN_H
#define SCISTATS_MIN_H

// C++
#include <algorithm>

// External
#include <async++.h>
#include <range/v3/iterator/concepts.hpp>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>

namespace scistats {
    /// Sequential min value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    min(scistats::execution::sequenced_policy, Iterator begin, Iterator end) {
        return *std::min_element(begin, end);
    }

    /// Parallel min value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    min(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        return async::parallel_reduce(
            async::make_range(std::next(begin), end), *begin,
            [](value_type x, value_type y) { return x < y ? x : y; });
    }

    template <class Iterator>
    std::enable_if_t<ranges::input_iterator<Iterator>,
                     typename Iterator::value_type>
    min(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 1000) {
            return scistats::min(scistats::execution::seq, begin, end);
        } else {
            return scistats::min(scistats::execution::par, begin, end);
        }
    }

    template <class Range>
    auto min(scistats::execution::sequenced_policy e, const Range &c) {
        return scistats::min(e, c.begin(), c.end());
    }

    template <class Range>
    auto min(scistats::execution::parallel_policy e, const Range &c) {
        return scistats::min(e, c.begin(), c.end());
    }

    template <class Range> auto min(const Range &c) {
        return scistats::min(c.begin(), c.end());
    }

    template <class VALUE_TYPE>
    std::enable_if_t<!ranges::input_iterator<VALUE_TYPE>, VALUE_TYPE>
    min(VALUE_TYPE a, VALUE_TYPE b) {
        return std::min(a, b);
    }

    template <class VALUE_TYPE, class... Args>
    std::enable_if_t<!ranges::input_iterator<VALUE_TYPE>, VALUE_TYPE>
    min(VALUE_TYPE a, VALUE_TYPE b, Args &&... args) {
        return std::min(a, scistats::min(b, std::forward<Args>(args)...));
    }

} // namespace scistats

#endif // SCISTATS_MIN_H
