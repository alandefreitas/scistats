//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MEAN_H
#define SCISTATS_MEAN_H

// C++
#include <algorithm>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>

namespace scistats {
    /// Sequential mean value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    mean(scistats::execution::sequenced_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        return_type m{0};
        size_t c{0};
        while (begin != end) {
            m += *begin;
            ++begin;
            ++c;
        }
        return m / c;
    }

    /// Parallel mean value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    mean(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;
        value_type sum = async::parallel_reduce(
            async::make_range(begin, end), value_type{0},
            [](value_type x, value_type y) { return x + y; });
        return static_cast<return_type>(sum) / std::distance(begin, end);
    }

    template <class Iterator> auto mean(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 1000) {
            return mean(scistats::execution::seq, begin, end);
        } else {
            return mean(scistats::execution::par, begin, end);
        }
    }

    template <class Range>
    auto mean(scistats::execution::sequenced_policy e, const Range &c) {
        return mean(e, c.begin(), c.end());
    }

    template <class Range>
    auto mean(scistats::execution::parallel_policy e, const Range &c) {
        return mean(e, c.begin(), c.end());
    }

    template <class Range> auto mean(const Range &c) {
        return mean(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MEAN_H
