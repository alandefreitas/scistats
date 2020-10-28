//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MAX_H
#define SCISTATS_MAX_H

// C++
#include <algorithm>

// External
#include <async++.h>
#include <range/v3/iterator/concepts.hpp>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>

namespace scistats {
    /// Sequential max value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    max(scistats::execution::sequenced_policy, Iterator begin, Iterator end) {
        return *std::max_element(begin, end);
    }

    /// Parallel max value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    max(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        return async::parallel_reduce(
            async::make_range(std::next(begin), end), *begin,
            [](value_type x, value_type y) { return x > y ? x : y; });
    }

    template <class Iterator>
    std::enable_if_t<ranges::input_iterator<Iterator>,
                     typename Iterator::value_type>
    max(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 1000) {
            return scistats::max(scistats::execution::seq, begin, end);
        } else {
            return scistats::max(scistats::execution::par, begin, end);
        }
    }

    template <class Range>
    auto max(scistats::execution::sequenced_policy e, const Range &c) {
        return scistats::max(e, c.begin(), c.end());
    }

    template <class Range>
    auto max(scistats::execution::parallel_policy e, const Range &c) {
        return scistats::max(e, c.begin(), c.end());
    }

    template <class Range> auto max(const Range &c) {
        return scistats::max(c.begin(), c.end());
    }

    template <class VALUE_TYPE>
    std::enable_if_t<!ranges::input_iterator<VALUE_TYPE>, VALUE_TYPE>
    max(VALUE_TYPE a, VALUE_TYPE b) {
        return std::max(a, b);
    }

    template <class VALUE_TYPE, class... Args>
    std::enable_if_t<!ranges::input_iterator<VALUE_TYPE>, VALUE_TYPE>
    max(VALUE_TYPE a, VALUE_TYPE b, Args &&... args) {
        return std::max(a, scistats::max(b, std::forward<Args>(args)...));
    }

} // namespace scistats

#endif // SCISTATS_MAX_H
