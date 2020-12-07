//
// Created by Alan Freitas on 12/4/20.
//

#ifndef SCISTATS_ALMOST_EQUAL_H
#define SCISTATS_ALMOST_EQUAL_H

#include <cmath>
#include <limits>
#include <scistats/common/concepts.h>
#include <scistats/math/abs.h>
#include <type_traits>

namespace scistats {
    template <Floating T>
    bool almost_equal(T x, T y, int units_in_last_place = 2) {
        // the machine epsilon has to be scaled to the magnitude of the values
        // used and multiplied by the desired precision in ULPs (units in the
        // last place)
        auto diff = scistats::abs(x - y);
        auto eps = std::numeric_limits<T>::epsilon() * std::fabs(x + y) *
                   units_in_last_place;
        return diff <= eps ||
               diff < std::numeric_limits<T>::min(); // unless the result is
                                                     // subnormal
    }

    template <Integer T>
    bool almost_equal(T x, T y, int units_in_last_place = 0) {
        return std::max(x, y) - std::min(x, y) <= units_in_last_place;
    }
} // namespace scistats

#endif // SCISTATS_ALMOST_EQUAL_H
