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

namespace scistats {
    /// \brief Sequential min
    template <Iterator T>
    value_type<T> min(execution::sequenced_policy, T begin, T end) {
        if (std::distance(begin, end) == 0) {
            return NaN<value_type<T>>();
        } else {
            return *std::min_element(begin, end);
        }
    }

    /// \brief Parallel min
    template <Iterator T>
    value_type<T> min(execution::parallel_policy, T begin, T end) {
        return async::parallel_reduce(
            async::make_range(std::next(begin), end), *begin,
            [](value_type<T> x, value_type<T> y) { return x < y ? x : y; });
    }

    /// \brief Threshold for using the parallel version of min
    constexpr size_t implicit_parallel_min_threshold = 1000;

    /// \brief Iterator min with implicit policy
    template <Iterator T>
    value_type<T> min(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_min_threshold;
        if (run_seq) {
            return min(execution::seq, begin, end);
        } else {
            return min(execution::par, begin, end);
        }
    }

    /// \brief Range min with policy
    template <ExecutionPolicy P, Range T>
    auto min(P e, T &c) {
        return min(e, c.begin(), c.end());
    }

    /// \brief Range min
    template <Range T>
    auto min(T &c) {
        return scistats::min(c.begin(), c.end());
    }

    /// \brief Elements min
    template <class T>
    T min(T a, T b) {
        return std::min(a, b);
    }

    /// \brief Elements min
    template <class T, class... Ts>
    T min(T a, T b, Ts &&... args) {
        return std::min(a, min(b, std::forward<Ts>(args)...));
    }

} // namespace scistats

#endif // SCISTATS_MIN_H
