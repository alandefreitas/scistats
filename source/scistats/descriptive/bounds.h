//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_BOUNDS_H
#define SCISTATS_BOUNDS_H

// C++
#include <algorithm>

// External
#include <async++.h>

// Internal
#include <scistats/common/execution.h>
#include <scistats/common/type_traits.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// \brief Sequential bounds
    template <Iterator T>
    std::pair<value_type<T>, value_type<T>> bounds(execution::sequenced_policy,
                                                   T begin, T end) {
        if (std::distance(begin, end) == 0) {
            return std::make_pair(NaN<value_type<T>>, NaN<value_type<T>>);
        } else {
            auto p = std::minmax_element(begin, end);
            return std::make_pair(*p.first, *p.second);
        }
    }

    /// \brief Parallel bounds
    template <Iterator T>
    std::pair<value_type<T>, value_type<T>> bounds(execution::parallel_policy,
                                                   T begin, T end) {
        using value_pair = std::pair<value_type<T>, value_type<T>>;
        return async::parallel_reduce(
            async::make_range(std::next(begin), end),
            value_pair{*begin, *begin}, [](auto x, auto y) {
                // y might be value_type or value_pair
                if constexpr (std::is_same_v<decltype(y), value_type<T>>) {
                    if (x.first < y) {
                        if (x.second > y) {
                            return x;
                        } else {
                            return value_pair{x.first, y};
                        }
                    } else {
                        if (x.second > y) {
                            return value_pair{y, x.second};
                        } else {
                            return value_pair{y, y};
                        }
                    }
                } else {
                    if (x.first < y.first) {
                        if (x.second > y.second) {
                            return x;
                        } else {
                            return value_pair{x.first, y.second};
                        }
                    } else {
                        if (x.second > y.second) {
                            return value_pair{y.first, x.second};
                        } else {
                            return y;
                        }
                    }
                }
            });
    }

    /// \brief Threshold for using the parallel version of bounds
    constexpr size_t implicit_parallel_bounds_threshold = 1000;

    /// \brief Iterator bounds with implicit policy
    template <Iterator T>
    auto bounds(T begin, T end) {
        auto size = static_cast<size_t>(std::distance(begin, end));
        const bool run_seq = size < implicit_parallel_bounds_threshold;
        if (run_seq) {
            return bounds(execution::seq, begin, end);
        } else {
            return bounds(execution::par, begin, end);
        }
    }

    /// \brief Range bounds with policy
    template <ExecutionPolicy P, Range T>
    auto bounds(P e, T &c) {
        return bounds(e, c.begin(), c.end());
    }

    /// \brief Range bounds
    template <Range T>
    auto bounds(T &c) {
        return bounds(c.begin(), c.end());
    }

    /// \brief Elements bounds
    template <class T>
    auto bounds(T a, T b) {
        return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
    }

    /// \brief Elements bounds
    template <class T>
    auto bounds(std::pair<T, T> p) {
        return p.first < p.second ? std::make_pair(p.first, p.second)
                                  : std::make_pair(p.second, p.first);
    }

    /// \brief Elements bounds
    template <class T>
    auto bounds(T a, std::pair<T, T> p) {
        auto [b, c] = p.first < p.second ? std::make_pair(p.first, p.second)
                                         : std::make_pair(p.second, p.first);
        return std::make_pair(a < b ? a : b, c < a ? a : c);
    }

    /// \brief Elements bounds
    template <class T, class... Ts>
    auto bounds(T a, std::pair<T, T> b, Ts &&... args) {
        return bounds(a, bounds(b, std::forward<Ts>(args)...));
    }

    /// \brief Elements bounds
    template <class T, class... Ts>
    auto bounds(T a, T b, Ts &&... args) {
        return bounds(a, bounds(b, std::forward<Ts>(args)...));
    }

} // namespace scistats

#endif // SCISTATS_BOUNDS_H
