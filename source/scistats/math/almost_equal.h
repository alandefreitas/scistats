//
// Created by Alan Freitas on 12/4/20.
//

#ifndef SCISTATS_ALMOST_EQUAL_H
#define SCISTATS_ALMOST_EQUAL_H

#include <cmath>
#include <limits>
#include <scistats/common/concepts.h>
#include <scistats/math/abs.h>
#include <scistats/math/constants.h>
#include <type_traits>

namespace scistats {
    template <Floating T>
    bool almost_equal(T x, T y, int units_in_last_place = 2) {
        const auto scale_magnitude = std::fabs(x + y);
        const auto eps = epsilon<T>(scale_magnitude) * units_in_last_place;
        auto diff = scistats::abs(x - y);
        if (diff <= eps) {
            return true;
        } else {
            const bool result_is_subnormal = diff < min<T>();
            if (result_is_subnormal) {
                return true;
            }
        }
        return false;
    }

    template <Integer T>
    bool almost_equal(T x, T y, int units_in_last_place = 0) {
        return std::max(x, y) - std::min(x, y) <= units_in_last_place;
    }
} // namespace scistats

#endif // SCISTATS_ALMOST_EQUAL_H
