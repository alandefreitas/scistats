//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_TGAMMA_H
#define SCISTATS_TGAMMA_H

#include <cmath>
#include <scistats/common/concepts.h>

namespace scistats {
    template <Floating T>
    T tgamma(T x) {
        if constexpr (sizeof(T) == sizeof(float)) {
            return std::tgammaf(x);
        } else if constexpr (sizeof(T) == sizeof(double)) {
            return std::tgamma(x);
        } else if constexpr (sizeof(T) == sizeof(long double)) {
            return std::tgammal(x);
        } else {
            return static_cast<T>(std::tgammal(static_cast<long double>(x)));
        }
    }
} // namespace scistats

#endif // SCISTATS_TGAMMA_H
