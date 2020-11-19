//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_PROD_H
#define SCISTATS_PROD_H

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
    /// \brief Sequential prod
    template <Iterator T>
    auto prod(execution::sequenced_policy, T begin, T end) {
        return std::accumulate(
            begin, end, value_type<T>{1},
            [](value_type<T> x, value_type<T> y) { return x * y; });
    }

    /// \brief Parallel prod
    template <Iterator T>
    auto prod(execution::parallel_policy, T begin, T end) {
        return async::parallel_reduce(
            async::make_range(begin, end), value_type<T>{1},
            [](value_type<T> x, value_type<T> y) { return x * y; });
    }

    /// \brief Auto-policy prod
    template <Iterator T>
    auto prod(T begin, T end) {
        if (std::distance(begin, end) < 1000) {
            return prod(execution::seq, begin, end);
        } else {
            return prod(execution::par, begin, end);
        }
    }

    /// \brief Range prod with policy
    template <ExecutionPolicy P, Range T>
    auto prod(P e, T &c) {
        return prod(e, c.begin(), c.end());
    }

    /// \brief Range prod
    /// Views are not const
    /// http://ericniebler.github.io/range-v3/index.html#autotoc_md6
    template <Range T>
    auto prod(T &c) {
        return prod(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_PROD_H
