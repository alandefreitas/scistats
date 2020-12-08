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
#include <scistats/descriptive/mean.h>

namespace scistats {
    /// \brief Iterator cov with explicit policy
    template <ExecutionPolicy P, Iterator T1, Iterator T2>
    promote<value_type<T1>> cov(P p, T1 begin_a, T1 end_a, T2 begin_b,
                                T2 end_b) {
        using value_type = value_type<T1>;
        using return_type = promote<value_type>;

        auto a_size = std::distance(begin_a, end_a);
        auto b_size = std::distance(begin_b, end_b);
        auto n = std::min(a_size, b_size);

        auto range_a = ranges::views::counted(begin_a, n);
        auto range_b = ranges::views::counted(begin_b, n);

        value_type sum_a = sum(p, range_a);
        value_type sum_b = sum(p, range_b);

        // c_i = (a_i - sum_a)/n * (b_i - sum_b)/n
        auto range_c = ranges::views::zip_with(
            [&](auto a, auto b) {
                const return_type t1 = static_cast<return_type>(a) -
                                       static_cast<return_type>(sum_a) / n;
                const return_type t2 = static_cast<return_type>(b) -
                                       static_cast<return_type>(sum_b) / n;
                return t1 * t2;
            },
            range_a, range_b);

        return_type c = sum(p, range_c);
        return c / (n <= 1 ? 1 : n - 1);
    }

    /// \brief Threshold for using the parallel version of cov
    constexpr size_t implicit_parallel_cov_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator cov with implicit policy
    template <Iterator T1, Iterator T2>
    auto cov(T1 begin_a, T1 end_a, T2 begin_b, T2 end_b) {
        auto size_a = static_cast<size_t>(std::distance(begin_a, end_a));
        auto size_b = static_cast<size_t>(std::distance(begin_b, end_b));
        const bool run_seq_a = size_a < implicit_parallel_cov_threshold;
        const bool run_seq_b = size_b < implicit_parallel_cov_threshold;
        if (run_seq_a || run_seq_b) {
            return cov(execution::seq, begin_a, end_a, begin_b, end_b);
        } else {
            return cov(execution::par, begin_a, end_a, begin_b, end_b);
        }
    }

    /// \brief Range cov with explicit policy
    template <ExecutionPolicy P, Range T1, Range T2>
    auto cov(P e, T1 &a, T2 &b) {
        return cov(e, a.begin(), a.end(), b.begin(), b.end());
    }

    /// \brief Range cov with implicit policy
    template <Range T1, Range T2>
    auto cov(T1 &a, T2 &b) {
        return cov(a.begin(), a.end(), b.begin(), b.end());
    }

} // namespace scistats

#endif // SCISTATS_COV_H
