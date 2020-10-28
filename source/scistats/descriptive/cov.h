//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_COV_H
#define SCISTATS_COV_H

// C++
#include <algorithm>
#include <cmath>
#include <numeric>

// External
#include <async++.h>
#include <range/v3/view/counted.hpp>
#include <range/v3/view/zip_with.hpp>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/promote.h>
#include <scistats/descriptive/mean.h>

namespace scistats {
    /// Sequential cov value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    cov(scistats::execution::sequenced_policy, Iterator begin_a, Iterator end_a,
        Iterator begin_b, Iterator end_b) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;

        auto a_size = std::distance(begin_a, end_a);
        auto b_size = std::distance(begin_b, end_b);
        auto n = std::min(a_size, b_size);
        value_type sum1 = std::accumulate(begin_a, end_a, value_type(0));
        value_type sum2 = std::accumulate(begin_b, end_b, value_type(0));
        return_type c{0};
        for (size_t i = 0; i < n; ++i) {
            return_type t1 = static_cast<return_type>(*begin_a) -
                             static_cast<return_type>(sum1) / n;
            return_type t2 = static_cast<return_type>(*begin_b) -
                             static_cast<return_type>(sum2) / n;
            c += t1 * t2;
            ++begin_a;
            ++begin_b;
        }

        return c / (n - 1);
    }

    /// Parallel cov value of sequence
    template <class Iterator>
    promote<typename std::iterator_traits<Iterator>::value_type>
    cov(scistats::execution::parallel_policy, Iterator begin_a, Iterator end_a,
        Iterator begin_b, Iterator end_b) {
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using return_type =
            promote<typename std::iterator_traits<Iterator>::value_type>;

        auto a_size = std::distance(begin_a, end_a);
        auto b_size = std::distance(begin_b, end_b);
        auto n = std::min(a_size, b_size);

        value_type sum1 = async::parallel_reduce(
            async::make_range(begin_a, end_a), value_type{0},
            [](value_type x, value_type y) { return x + y; });

        value_type sum2 = async::parallel_reduce(
            async::make_range(begin_b, end_b), value_type{0},
            [](value_type x, value_type y) { return x + y; });

        auto range_a = ranges::views::counted(begin_a, n);
        auto range_b = ranges::views::counted(begin_b, n);

        auto range_c = ranges::views::zip_with(
            [&](auto a, auto b) {
                return_type t1 = static_cast<return_type>(a) -
                                 static_cast<return_type>(sum1) / n;
                return_type t2 = static_cast<return_type>(b) -
                                 static_cast<return_type>(sum2) / n;
                return t1 * t2;
            },
            range_a, range_b);

        return_type c = async::parallel_reduce(
            range_c, return_type{0},
            [](return_type x, return_type y) { return x + y; });

        return c / (n - 1);
    }

    template <class Iterator>
    auto cov(Iterator begin_a, Iterator end_a, Iterator begin_b,
             Iterator end_b) {
        if (std::distance(begin_a, end_a) < 1000 &&
            std::distance(begin_b, end_b) < 1000) {
            return cov(scistats::execution::seq, begin_a, end_a, begin_b,
                       end_b);
        } else {
            return cov(scistats::execution::par, begin_a, end_a, begin_b,
                       end_b);
        }
    }

    template <class Range>
    auto cov(scistats::execution::sequenced_policy e, const Range &a,
             const Range &b) {
        return cov(e, a.begin(), a.end(), b.begin(), b.end());
    }

    template <class Range>
    auto cov(scistats::execution::parallel_policy e, const Range &a,
             const Range &b) {
        return cov(e, a.begin(), a.end(), b.begin(), b.end());
    }

    template <class Range> auto cov(const Range &a, const Range &b) {
        return cov(a.begin(), a.end(), b.begin(), b.end());
    }

} // namespace scistats

#endif // SCISTATS_COV_H
