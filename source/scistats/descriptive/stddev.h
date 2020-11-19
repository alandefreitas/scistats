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
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/var.h>

namespace scistats {
    /// \brief Iterator stddev with explicit policy (mean provided)
    template <ExecutionPolicy P, Iterator T, Floating T2>
    promote<value_type<T>> stddev(P p, T begin, T end, T2 mean) {
        return std::sqrt(var(p, begin, end, mean));
    }

    /// \brief Iterator stddev with explicit policy
    template <ExecutionPolicy P, Iterator T>
    promote<value_type<T>> stddev(P p, T begin, T end) {
        auto m = mean(p, begin, end);
        return stddev(p, begin, end, m);
    }

    /// \brief Threshold for using the parallel version of stddev
    constexpr size_t implicit_parallel_stddev_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator stddev with implicit policy (mean provided)
    template <Iterator T, Floating T2>
    auto stddev(T begin, T end, T2 mean) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_stddev_threshold;
        if (run_seq) {
            return stddev(execution::seq, begin, end, mean);
        } else {
            return stddev(execution::par, begin, end, mean);
        }
    }

    /// \brief Iterator stddev with implicit policy
    template <Iterator T>
    auto stddev(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_stddev_threshold;
        if (run_seq) {
            return stddev(execution::seq, begin, end);
        } else {
            return stddev(execution::par, begin, end);
        }
    }

    /// \brief Range stddev with explicit policy (mean provided)
    template <ExecutionPolicy P, Range T, Floating T2>
    auto stddev(P e, T &c, T2 mean) {
        return stddev(e, c.begin(), c.end(), mean);
    }

    /// \brief Range stddev with explicit policy
    template <ExecutionPolicy P, Range T>
    auto stddev(P e, T &c) {
        return stddev(e, c.begin(), c.end());
    }

    /// \brief Range stddev with implicit policy (mean provided)
    template <Range T, Floating T2>
    auto stddev(T &c, T2 mean) {
        return stddev(c.begin(), c.end(), mean);
    }

    /// \brief Range stddev with implicit policy
    template <Range T>
    auto stddev(T &c) {
        return stddev(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_STDDEV_H
