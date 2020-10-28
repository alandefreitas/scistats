//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MODE_H
#define SCISTATS_MODE_H

// C++
#include <algorithm>
#include <map>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>

namespace scistats {
    /// Sequential mode value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    mode(scistats::execution::sequenced_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        std::map<value_type, size_t> counts;
        while (begin != end) {
            auto it = counts.find(*begin);
            if (it == counts.end()) {
                counts[*begin] = 1;
            } else {
                ++counts[*begin];
            }
            ++begin;
        }
        auto it =
            std::max_element(counts.begin(), counts.end(), [](auto a, auto b) {
                return a.second < b.second;
            });
        return it->first;
    }

    /// Parallel mode value of sequence
    template <class Iterator>
    typename std::iterator_traits<Iterator>::value_type
    mode(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        return mode(execution::seq, begin, end);
    }

    template <class Iterator> auto mode(Iterator begin, Iterator end) {
        return mode(scistats::execution::seq, begin, end);
    }

    template <class Range>
    auto mode(scistats::execution::sequenced_policy e, const Range &c) {
        return mode(e, c.begin(), c.end());
    }

    template <class Range>
    auto mode(scistats::execution::parallel_policy e, const Range &c) {
        return mode(e, c.begin(), c.end());
    }

    template <class Range> auto mode(const Range &c) {
        return mode(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MODE_H
