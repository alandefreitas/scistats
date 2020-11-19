//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_SUM_H
#define SCISTATS_SUM_H

// C++
#include <algorithm>
#include <numeric>

// External
#include <async++.h>
#include <range/v3/range/concepts.hpp>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/common/type_traits.h>

namespace scistats {
    /// \brief Sequential sum
    template <Iterator T>
    auto sum(execution::sequenced_policy, T begin, T end) {
        return std::accumulate(begin, end, value_type<T>{0});
    }

    /// \brief Parallel sum
    template <Iterator T>
    auto sum(execution::parallel_policy, T begin, T end) {
        return async::parallel_reduce(
            async::make_range(begin, end), value_type<T>{0},
            [](value_type<T> x, value_type<T> y) { return x + y; });
    }

    /// \brief Threshold for using the parallel version of sum
    constexpr size_t implicit_parallel_sum_threshold = 1000;

    /// \brief Iterator sum with implicit policy
    template <Iterator T>
    auto sum(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_sum_threshold;
        if (run_seq) {
            return sum(execution::seq, begin, end);
        } else {
            return sum(execution::par, begin, end);
        }
    }

    /// \brief Range sum with policy
    template <ExecutionPolicy P, Range T>
    auto sum(P e, T &c) {
        return sum(e, c.begin(), c.end());
    }

    /// \brief Range sum
    /// Views are not const
    /// http://ericniebler.github.io/range-v3/index.html#autotoc_md6
    template <Range T>
    auto sum(T &c) {
        return sum(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_SUM_H
