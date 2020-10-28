//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_STDDEV_H
#define SCISTATS_STDDEV_H

// C++
#include <algorithm>
#include <cmath>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>
#include <scistats/descriptive/mean.h>

namespace scistats {
    /// Sequential stddev value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    stddev(scistats::execution::sequenced_policy, Iterator begin,
           Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        auto m = mean(execution::par, begin, end);
        return_type sum{0.};
        size_t c{0};
        while (begin != end) {
            sum += std::pow(*begin - m, 2.);
            ++begin;
            ++c;
        }
        return std::sqrt(sum / (c - 1));
    }

    /// Parallel stddev value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    stddev(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        return_type m = mean(execution::par, begin, end);
        return_type sum = async::parallel_map_reduce(
            async::make_range(begin, end), return_type{0.},
            [&m](return_type x) {
                return std::pow(static_cast<return_type>(x) - m, 2.);
            },
            [](return_type x, return_type y) { return x + y; });
        return std::sqrt(sum / (std::distance(begin, end) - 1));
    }

    template <class Iterator> auto stddev(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 1000) {
            return stddev(scistats::execution::seq, begin, end);
        } else {
            return stddev(scistats::execution::par, begin, end);
        }
    }

    template <class Range>
    auto stddev(scistats::execution::sequenced_policy e, const Range &c) {
        return stddev(e, c.begin(), c.end());
    }

    template <class Range>
    auto stddev(scistats::execution::parallel_policy e, const Range &c) {
        return stddev(e, c.begin(), c.end());
    }

    template <class Range> auto stddev(const Range &c) {
        return stddev(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_STDDEV_H
