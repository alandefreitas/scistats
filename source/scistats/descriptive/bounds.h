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

namespace scistats {
    /// Sequential bounds value of sequence
    template <class Iterator>
    auto bounds(scistats::execution::sequenced_policy, Iterator begin,
                Iterator end) {
        auto p = std::minmax_element(begin, end);
        return std::make_pair(*p.first, *p.second);
    }

    /// Parallel bounds value of sequence
    template <class Iterator>
    std::pair<typename std::iterator_traits<Iterator>::value_type,
              typename std::iterator_traits<Iterator>::value_type>
    bounds(scistats::execution::parallel_policy, Iterator begin, Iterator end) {
        using value_type =
            std::decay_t<typename std::iterator_traits<Iterator>::value_type>;
        using value_pair = std::pair<value_type, value_type>;
        return async::parallel_reduce(
            async::make_range(std::next(begin), end),
            value_pair{*begin, *begin}, [](auto x, auto y) {
                // y might be value_type or value_pair
                if constexpr (std::is_same_v<decltype(y), value_type>) {
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

    template <class Iterator> auto bounds(Iterator begin, Iterator end) {
        if (std::distance(begin, end) < 1000) {
            return scistats::bounds(scistats::execution::seq, begin, end);
        } else {
            return scistats::bounds(scistats::execution::par, begin, end);
        }
    }

    template <class Range>
    auto bounds(scistats::execution::sequenced_policy e, const Range &c) {
        return scistats::bounds(e, c.begin(), c.end());
    }

    template <class Range>
    auto bounds(scistats::execution::parallel_policy e, const Range &c) {
        return scistats::bounds(e, c.begin(), c.end());
    }

    template <class Range> auto bounds(const Range &c) {
        return scistats::bounds(c.begin(), c.end());
    }

} // namespace scistats

#endif // SCISTATS_BOUNDS_H
