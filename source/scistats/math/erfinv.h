//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_ERFINV_H
#define SCISTATS_ERFINV_H

// C++
#include <cmath>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/math/almost_equal.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// erfinv
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T>
    T erfinv(T x) {
        if (x < -1 || x > 1) {
            return NaN<T>();
        } else if (almost_equal(x, 1.0)) {
            return std::numeric_limits<T>::infinity();
        } else if (almost_equal(x, -1.0)) {
            return -std::numeric_limits<T>::infinity();
        }

        constexpr T LN2 = 6.931471805599453094172321214581e-1L;

        constexpr T A0 = 1.1975323115670912564578e0L;
        constexpr T A1 = 4.7072688112383978012285e1L;
        constexpr T A2 = 6.9706266534389598238465e2L;
        constexpr T A3 = 4.8548868893843886794648e3L;
        constexpr T A4 = 1.6235862515167575384252e4L;
        constexpr T A5 = 2.3782041382114385731252e4L;
        constexpr T A6 = 1.1819493347062294404278e4L;
        constexpr T A7 = 8.8709406962545514830200e2L;

        constexpr T B0 = 1.0000000000000000000e0L;
        constexpr T B1 = 4.2313330701600911252e1L;
        constexpr T B2 = 6.8718700749205790830e2L;
        constexpr T B3 = 5.3941960214247511077e3L;
        constexpr T B4 = 2.1213794301586595867e4L;
        constexpr T B5 = 3.9307895800092710610e4L;
        constexpr T B6 = 2.8729085735721942674e4L;
        constexpr T B7 = 5.2264952788528545610e3L;

        constexpr T C0 = 1.42343711074968357734e0L;
        constexpr T C1 = 4.63033784615654529590e0L;
        constexpr T C2 = 5.76949722146069140550e0L;
        constexpr T C3 = 3.64784832476320460504e0L;
        constexpr T C4 = 1.27045825245236838258e0L;
        constexpr T C5 = 2.41780725177450611770e-1L;
        constexpr T C6 = 2.27238449892691845833e-2L;
        constexpr T C7 = 7.74545014278341407640e-4L;

        constexpr T D0 = 1.4142135623730950488016887e0L;
        constexpr T D1 = 2.9036514445419946173133295e0L;
        constexpr T D2 = 2.3707661626024532365971225e0L;
        constexpr T D3 = 9.7547832001787427186894837e-1L;
        constexpr T D4 = 2.0945065210512749128288442e-1L;
        constexpr T D5 = 2.1494160384252876777097297e-2L;
        constexpr T D6 = 7.7441459065157709165577218e-4L;
        constexpr T D7 = 1.4859850019840355905497876e-9L;

        constexpr T E0 = 6.65790464350110377720e0L;
        constexpr T E1 = 5.46378491116411436990e0L;
        constexpr T E2 = 1.78482653991729133580e0L;
        constexpr T E3 = 2.96560571828504891230e-1L;
        constexpr T E4 = 2.65321895265761230930e-2L;
        constexpr T E5 = 1.24266094738807843860e-3L;
        constexpr T E6 = 2.71155556874348757815e-5L;
        constexpr T E7 = 2.01033439929228813265e-7L;

        constexpr T F0 = 1.414213562373095048801689e0L;
        constexpr T F1 = 8.482908416595164588112026e-1L;
        constexpr T F2 = 1.936480946950659106176712e-1L;
        constexpr T F3 = 2.103693768272068968719679e-2L;
        constexpr T F4 = 1.112800997078859844711555e-3L;
        constexpr T F5 = 2.611088405080593625138020e-5L;
        constexpr T F6 = 2.010321207683943062279931e-7L;
        constexpr T F7 = 2.891024605872965461538222e-15L;

        T abs_x = abs(x);

        if (abs_x <= 0.85) {
            T r = 0.180625 - 0.25 * x * x;
            T num =
                (((((((A7 * r + A6) * r + A5) * r + A4) * r + A3) * r + A2) *
                      r +
                  A1) *
                     r +
                 A0);
            T den =
                (((((((B7 * r + B6) * r + B5) * r + B4) * r + B3) * r + B2) *
                      r +
                  B1) *
                     r +
                 B0);
            return x * num / den;
        }

        T r = sqrt(LN2 - log(1.0 - abs_x));

        T num, den;
        if (r <= 5.0) {
            r = r - 1.6;
            num = (((((((C7 * r + C6) * r + C5) * r + C4) * r + C3) * r + C2) *
                        r +
                    C1) *
                       r +
                   C0);
            den = (((((((D7 * r + D6) * r + D5) * r + D4) * r + D3) * r + D2) *
                        r +
                    D1) *
                       r +
                   D0);
        } else {
            r = r - 5.0;
            num = (((((((E7 * r + E6) * r + E5) * r + E4) * r + E3) * r + E2) *
                        r +
                    E1) *
                       r +
                   E0);
            den = (((((((F7 * r + F6) * r + F5) * r + F4) * r + F3) * r + F2) *
                        r +
                    F1) *
                       r +
                   F0);
        }

        if (x < 0) {
            return -num / den;
        } else {
            return num / den;
        }
    }

    /// Estimate erfinv
    template <Floating T>
    T erfinv(T x, int nr_iter) {
        constexpr T k = 0.8862269254527580136490837416706L; // 0.5 * sqrt(pi)
        T y = erfinv(x);
        while (nr_iter-- > 0) {
            y -= k * (std::erf(y) - x) / std::exp(-y * y);
        }
        return y;
    }

    /// Simple erfinv
    /// A simpler version of erfinv
    template <Floating T>
    T erfinv_simple(T x) {
        T tt1, tt2, lnx, sgn;
        sgn = (x < 0) ? -1.0 : 1.0;

        // x = 1 - x*x;
        x = (1.0 - x) * (1.0 + x);
        lnx = log(x);

        tt1 = 2 / (pi<T>() * 0.147) + 0.5 * lnx;
        tt2 = 1 / (0.147) * lnx;

        return (sgn * sqrt(-tt1 + sqrt(tt1 * tt1 - tt2)));
    }
} // namespace scistats

#endif // SCISTATS_ERFINV_H
