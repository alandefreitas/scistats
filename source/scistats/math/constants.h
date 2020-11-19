//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_CONSTANTS_H
#define SCISTATS_CONSTANTS_H

#include <scistats/common/concepts.h>

namespace scistats {
    template <Floating T>
    constexpr T pi = static_cast<T>(3.1415926535897932384626433832795L);

    template <Floating T>
    constexpr T epsilon = static_cast<T>(1.0e-30l);

    template <Floating T = long double>
    constexpr T inf = std::numeric_limits<T>::infinity();

    template <typename T>
    constexpr T NaN = std::numeric_limits<T>::quiet_NaN();
} // namespace scistats

#endif // SCISTATS_CONSTANTS_H
