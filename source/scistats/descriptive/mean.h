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
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/common/type_traits.h>
#include <scistats/math/sum.h>

namespace scistats {
    /// \brief Iterator mean with explicit policy
    template <ExecutionPolicy P, Iterator T>
    promote<value_type<T>> mean(P p, T begin, T end) {
        using return_type = promote<value_type<T>>;
        auto numerator = static_cast<return_type>(sum(p, begin, end));
        auto denominator = static_cast<return_type>(std::distance(begin, end));
        return numerator / denominator;
    }

    /// \brief Threshold for using the parallel version of mean
    constexpr size_t implicit_parallel_mean_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator mean with implicit policy
    template <Iterator T>
    auto mean(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_mean_threshold;
        if (run_seq) {
            return mean(scistats::execution::seq, begin, end);
        } else {
            return mean(scistats::execution::par, begin, end);
        }
    }

    /// \brief Range mean with explicit policy
    template <ExecutionPolicy P, Range T>
    auto mean(P e, T &c) {
        return mean(e, c.begin(), c.end());
    }

    /// \brief Range mean with implicit policy
    template <Range T>
    auto mean(T &c) {
        return mean(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MEAN_H
