//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_PERCENTILE_H
#define SCISTATS_PERCENTILE_H

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
    /// There's no implementation of the parallel policy
    /// because most stable releases of C++20 compilers
    /// don't include execution policies for nth_element
    template <ExecutionPolicy P, Iterator T, Integer T2>
    auto percentile([[maybe_unused]] P p, T begin, T end, T2 perc) {
        size_t size = std::distance(begin, end);
        const bool is_odd = size & 1U;
        T upper_middle_element =
            std::next(begin, std::distance(begin, end) * perc / 100);
        if (!std::is_sorted(begin, end)) {
            std::nth_element(begin, upper_middle_element, end);
        }
        if (is_odd) {
            return static_cast<promote<value_type<T>>>(*upper_middle_element);
        } else {
            T lower_middle_element =
                std::max_element(begin, upper_middle_element);
            return static_cast<promote<value_type<T>>>(*upper_middle_element +
                                                       *lower_middle_element) /
                   static_cast<promote<value_type<T>>>(2);
        }
    }

    /// \brief Iterator mean with explicit policy
    template <ExecutionPolicy P, ConstIterator T, Integer T2>
    auto percentile(P p, T begin, T end, T2 perc) {
        std::vector<std::decay_t<value_type<T>>> copy(begin, end);
        return percentile(p, copy.begin(), copy.end(), perc);
    }

    /// \brief Threshold for using the parallel version of percentile
    constexpr size_t implicit_parallel_percentile_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator percentile with implicit policy
    template <Iterator T, Integer T2>
    auto percentile(T begin, T end, T2 perc) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_percentile_threshold;
        if (run_seq) {
            return percentile(scistats::execution::seq, begin, end, perc);
        } else {
            return percentile(scistats::execution::par, begin, end, perc);
        }
    }

    /// \brief Range percentile with explicit policy
    template <ExecutionPolicy P, Range T, Integer T2>
    auto percentile(P e, T &c, T2 perc) {
        return percentile(e, c.begin(), c.end(), perc);
    }

    /// \brief Range percentile with implicit policy
    template <Range T, Integer T2>
    auto percentile(T &c, T2 perc) {
        return percentile(c.begin(), c.end(), perc);
    }

} // namespace scistats

#endif // SCISTATS_PERCENTILE_H
