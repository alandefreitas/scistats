//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_CONSTANTS_H
#define SCISTATS_CONSTANTS_H

#include <cmath>
#include <scistats/common/concepts.h>
#include <scistats/common/type_traits.h>

namespace scistats {
    /// \brief The constant pi
    template <Floating T = float>
    constexpr T pi() {
        return static_cast<T>(3.1415926535897932384626433832795L);
    }

    /// \brief A tiny tiny number
    template <Number T = float>
    constexpr T epsilon(T scale_magnitude = static_cast<T>(1.)) {
        const T machine_epsilon = std::numeric_limits<T>::epsilon();
        return machine_epsilon * scale_magnitude;
    }

    /// \brief Infinity
    template <Number T = float>
    constexpr T inf() {
        return std::numeric_limits<T>::infinity();
    }

    /// \brief Minimum number
    template <Number T = float>
    constexpr T min() {
        return std::numeric_limits<T>::min();
    }

    /// \brief Maximum number
    template <Number T = float>
    constexpr T max() {
        return std::numeric_limits<T>::max();
    }

    /// \brief Not a number
    template <Number T = float>
    constexpr T NaN() {
        return std::numeric_limits<T>::quiet_NaN();
    }

    /// \brief The base of exponentials
    /// Euler's number
    /// The base of the natural logarithm
    template <Floating T = float>
    constexpr promote<T> e() {
        return std::exp(promote<T>(1.0));
    }

    /// \brief Euler–Mascheroni constant / or Euler's gamma
    template <Floating T = float>
    constexpr T euler() {
        return static_cast<T>(
            0.57721566490153286060651209008240243104215933593992);
    }

    /// \brief The base-2 logarithm of e
    template <Floating T = float>
    constexpr T log2_e() {
        return std::log2(e<T>());
    }

    /// \brief The base-10 logarithm of e
    template <Floating T = float>
    constexpr T log10_e() {
        return std::log10(e<T>());
    }

    /// \brief The square root of two
    template <Floating T = float>
    constexpr promote<T> sqrt2() {
        return static_cast<promote<T>>(std::sqrt(static_cast<double>(2.0)));
    }

    /// \brief The square root of one-half
    template <Floating T = float>
    constexpr T sqrt1_2() {
        return static_cast<promote<T>>(std::sqrt(static_cast<double>(0.5)));
    }

    /// \brief The square root of three
    template <Floating T = float>
    constexpr promote<T> sqrt3() {
        return static_cast<promote<T>>(std::sqrt(static_cast<double>(3.0)));
    }

    /// \brief Pi divided by two
    template <Floating T = float>
    constexpr T pi_2() {
        return pi<T>() / static_cast<T>(2);
    }

    /// \brief Pi divided by four
    template <Floating T = float>
    constexpr T pi_4() {
        return pi<T>() / static_cast<T>(4);
    }

    /// \brief The square root of pi
    template <Floating T = float>
    constexpr T sqrt_pi() {
        return std::sqrt(pi<T>());
    }

    /// \brief Two divided by the square root of pi
    template <Floating T = float>
    constexpr T two_sqrt_pi() {
        return static_cast<T>(2) / sqrt_pi<T>();
    }

    /// \brief The reciprocal of pi (1./pi)
    template <Floating T = float>
    constexpr T one_by_pi() {
        return static_cast<T>(1) / pi<T>();
    }

    /// \brief Twice the reciprocal of pi
    template <Floating T = float>
    constexpr T two_by_pi() {
        return static_cast<T>(2) / pi<T>();
    }

    /// \brief The natural logarithm of ten
    template <Floating T = float>
    constexpr T ln10() {
        return std::log(static_cast<T>(10));
    }

    /// \brief The natural logarithm of two
    template <Floating T = float>
    constexpr T ln2() {
        return std::log(static_cast<T>(2));
    }

    /// \brief The natural logarithm of pi
    template <Floating T = float>
    constexpr T lnpi() {
        return std::log(pi<T>());
    }

} // namespace scistats

#endif // SCISTATS_CONSTANTS_H
