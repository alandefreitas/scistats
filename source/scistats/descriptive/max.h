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
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// \brief Sequential max
    template <Iterator T>
    value_type<T> max(execution::sequenced_policy, T begin, T end) {
        if (std::distance(begin, end) == 0) {
            return NaN<value_type<T>>;
        } else {
            return *std::max_element(begin, end);
        }
    }

    /// \brief Parallel max
    template <Iterator T>
    value_type<T> max(execution::parallel_policy, T begin, T end) {
        return async::parallel_reduce(
            async::make_range(std::next(begin), end), *begin,
            [](value_type<T> x, value_type<T> y) { return x > y ? x : y; });
    }

    /// \brief Threshold for using the parallel version of max
    constexpr size_t implicit_parallel_max_threshold = 1000;

    /// \brief Iterator max with implicit policy
    template <Iterator T>
    value_type<T> max(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_max_threshold;
        if (run_seq) {
            return max(execution::seq, begin, end);
        } else {
            return max(execution::par, begin, end);
        }
    }

    /// \brief Range max with policy
    template <ExecutionPolicy P, Range T>
    auto max(P e, T &c) {
        return max(e, c.begin(), c.end());
    }

    /// \brief Range max
    template <Range T>
    auto max(T &c) {
        return scistats::max(c.begin(), c.end());
    }

    /// \brief Elements max
    template <class T>
    T max(T a, T b) {
        // Note that this is different from std::max when there are
        // ties
        return b < a ? a : b;
    }

    /// \brief Elements max
    template <class T, class... Ts>
    T max(T a, T b, Ts &&... args) {
        return std::max(a, max(b, std::forward<Ts>(args)...));
    }

} // namespace scistats

#endif // SCISTATS_MAX_H
