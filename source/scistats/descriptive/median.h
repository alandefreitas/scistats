//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MEDIAN_H
#define SCISTATS_MEDIAN_H

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
    /// \brief Iterator median with explicit policy
    /// There's no implementation of the parallel policy
    /// because most stable releases of C++20 compilers
    /// don't include execution policies for nth_element
    template <ExecutionPolicy P, Iterator T>
    auto median([[maybe_unused]] P p, T begin, T end) {
        size_t size = std::distance(begin, end);
        const bool is_odd = size & 1U;
        T upper_middle_element = std::next(begin, size / 2);
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

    /// \brief Iterator median with explicit policy
    template <ExecutionPolicy P, ConstIterator T>
    auto median(P p, T begin, T end) {
        std::vector<std::decay_t<value_type<T>>> copy(begin, end);
        return median(p, copy.begin(), copy.end());
    }

    /// \brief Threshold for using the parallel version of median
    constexpr size_t implicit_parallel_median_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator median with implicit policy
    template <Iterator T>
    auto median(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_median_threshold;
        if (run_seq) {
            return median(scistats::execution::seq, begin, end);
        } else {
            return median(scistats::execution::par, begin, end);
        }
    }

    /// \brief Range median with explicit policy
    template <ExecutionPolicy P, Range T>
    auto median(P e, T &c) {
        return median(e, c.begin(), c.end());
    }

    /// \brief Range median with implicit policy
    template <Range T>
    auto median(T &c) {
        return median(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MEDIAN_H
