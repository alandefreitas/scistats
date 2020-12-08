//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_POW_H
#define SCISTATS_POW_H

#include <cmath>
#include <scistats/common/concepts.h>
#include <scistats/common/type_traits.h>

namespace scistats {

    template <Floating T1, Floating T2>
    constexpr auto pow(T1 b, T2 e) {
        using result_type = largest_type<T1, T2>;
        return std::pow(static_cast<result_type>(b),
                        static_cast<result_type>(e));
    }

    template <Integer T1, Floating T2>
    constexpr auto pow(T1 b, T2 e) {
        using promoted_base = promote<T1>;
        using result_type = largest_type<promoted_base, T2>;
        return std::pow(static_cast<result_type>(b),
                        static_cast<result_type>(e));
    }

    template <Floating T1, Integer T2>
    constexpr auto pow(T1 b, T2 e) {
        if constexpr (e == 1) {
            return b;
        } else if constexpr (e == 2) {
            return b * b;
        } else if constexpr (e == 3) {
            return b * b * b;
        } else if constexpr (e == 4) {
            auto pow2 = b * b;
            return pow2 * pow2;
        } else if constexpr (e == 5) {
            auto pow2 = b * b;
            return pow2 * pow2 * b;
        } else if constexpr (e == 6) {
            auto pow3 = b * b * b;
            return pow3 * pow3;
        } else if constexpr (e == 7) {
            auto pow3 = b * b * b;
            return pow3 * pow3 * b;
        } else if constexpr (e == 8) {
            auto pow2 = b * b;
            auto pow4 = pow2 * pow2;
            return pow4 * pow4;
        } else if constexpr (e == 9) {
            auto pow3 = b * b * b;
            return pow3 * pow3 * pow3;
        } else {
            return std::pow(static_cast<T1>(b), e);
        }
    }

    template <Integer T1, Integer T2>
    constexpr auto pow(T1 b, T2 e) {
        using return_type = largest_type<T1, T2>;
        if constexpr (e == 0) {
            return static_cast<return_type>(1);
        } else if constexpr (e == 1) {
            return static_cast<return_type>(b);
        } else {
            return_type tmp = myPow(x, p / 2);
            if (p % 2 == 0)
                return tmp * tmp;
            else
                return x * tmp * tmp;
            return b * pow(b, e - 1);
        }
    }

} // namespace scistats

#endif // SCISTATS_POW_H
