//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_VAR_H
#define SCISTATS_VAR_H

// C++
#include <algorithm>
#include <cmath>
#include <numeric>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/descriptive/mean.h>

namespace scistats {
    /// \brief Iterator var with explicit policy (mean provided)
    template <ExecutionPolicy P, Iterator T>
    promote<value_type<T>> var(P, T begin, T end, promote<value_type<T>> mean) {
        promote<value_type<T>> numerator{0.};
        if constexpr (std::is_same_v<P, execution::sequenced_policy>) {
            numerator =
                std::accumulate(begin, end, numerator, [&](auto a, auto b) {
                    return a + std::pow(static_cast<promote<value_type<T>>>(b) -
                                            mean,
                                        static_cast<promote<value_type<T>>>(2));
                });
        } else {
            numerator = async::parallel_map_reduce(
                async::range(begin, end), numerator,
                [&](auto a) {
                    return std::pow(static_cast<promote<value_type<T>>>(a) -
                                        mean,
                                    static_cast<promote<value_type<T>>>(2));
                },
                std::plus<>());
        }

        auto n = std::distance(begin, end);
        const auto denominator =
            static_cast<promote<value_type<T>>>(n < 2 ? n : n - 1);
        return numerator / denominator;
    }

    /// \brief Iterator var with explicit policy
    template <ExecutionPolicy P, Iterator T>
    promote<value_type<T>> var(P p, T begin, T end) {
        auto m = mean(p, begin, end);
        return var(p, begin, end, m);
    }

    /// \brief Threshold for using the parallel version of var
    constexpr size_t implicit_parallel_var_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator var with implicit policy (mean provided)
    template <Iterator T>
    auto var(T begin, T end, promote<value_type<T>> mean) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_var_threshold;
        if (run_seq) {
            return var(execution::seq, begin, end, mean);
        } else {
            return var(execution::par, begin, end, mean);
        }
    }

    /// \brief Iterator var with implicit policy
    template <Iterator T>
    auto var(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_var_threshold;
        if (run_seq) {
            return var(execution::seq, begin, end);
        } else {
            return var(execution::par, begin, end);
        }
    }

    /// \brief Range var with explicit policy (mean provided)
    template <ExecutionPolicy P, Range T>
    auto var(P e, T &c, promote<value_type<T>> mean) {
        return var(e, c.begin(), c.end(), mean);
    }

    /// \brief Range var with explicit policy
    template <ExecutionPolicy P, Range T>
    auto var(P e, T &c) {
        return var(e, c.begin(), c.end());
    }

    /// \brief Range var with implicit policy (mean provided)
    template <Range T>
    auto var(T &c, promote<value_type<T>> mean) {
        return var(c.begin(), c.end(), mean);
    }

    /// \brief Range var with implicit policy
    template <Range T>
    auto var(T &c) {
        return var(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_VAR_H
