//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_MODE_H
#define SCISTATS_MODE_H

// C++
#include <algorithm>
#include <map>

// External
#include <async++.h>
#include <range/v3/algorithm/max_element.hpp>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/common/type_traits.h>
#include <scistats/math/sum.h>

namespace scistats {
    /// \brief Iterator median with explicit policy
    template <ExecutionPolicy P, Iterator T>
    auto mode([[maybe_unused]] P p, T begin, T end) {
        if (std::is_sorted(begin, end)) {
            value_type<T> current_number = *begin;
            value_type<T> mode = current_number;
            size_t count = 1;
            size_t count_mode = 1;
            ++begin;
            while (begin != end) {
                if (*begin == current_number) {
                    ++count;
                } else {
                    if (count > count_mode) {
                        count_mode = count;
                        mode = current_number;
                    }
                    count = 1;
                    current_number = *begin;
                }
                ++begin;
            }
            return mode;
        } else {
            std::map<value_type<T>, size_t> counts;
            auto count_element = [&](const auto &el) {
                auto it = counts.find(el);
                if (it == counts.end()) {
                    counts[el] = 1;
                } else {
                    ++counts[el];
                }
            };

            // we cannot use async::parallel_for here
            // because std::map is not thread safe
            std::for_each(begin, end, count_element);

            auto it = ranges::max_element(
                counts, [](auto a, auto b) { return a.second < b.second; });
            return it->first;
        }
    }

    /// \brief Threshold for using the parallel version of mode
    constexpr size_t implicit_parallel_mode_threshold =
        implicit_parallel_sum_threshold;

    /// \brief Iterator mode with implicit policy
    template <Iterator T>
    auto mode(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_mode_threshold;
        if (run_seq) {
            return mode(scistats::execution::seq, begin, end);
        } else {
            return mode(scistats::execution::par, begin, end);
        }
    }

    /// \brief Range mode with explicit policy
    template <ExecutionPolicy P, Range T>
    auto mode(P e, T &c) {
        return mode(e, c.begin(), c.end());
    }

    /// \brief Range mode with implicit policy
    template <Range T>
    auto mode(T &c) {
        return mode(c.begin(), c.end());
    }

    /// \brief Range mode with implicit policy
    template <Range T>
    auto mode(const T &c) {
        return mode(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_MODE_H
