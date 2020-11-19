//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_BETA_INC_H
#define SCISTATS_BETA_INC_H

// C++
#include <cmath>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/math/abs.h>

namespace scistats {
    /// Incomplete beta function
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T>
    T beta_inc(T x, T a, T b) {
        constexpr T TINY = static_cast<T>(1.0e-30l);

        if (x < 0.0 || x > 1.0)
            return 1.0 / 0.0;

        // The continued fraction converges nicely for x < (a+1)/(a+b+2)
        if (x > (a + 1.0) / (a + b + 2.0)) {
            return (1.0 -
                    beta_inc(1.0 - x, b,
                             a)); // Use the fact that beta is symmetrical.
        }

        // Find the first part before the continued fraction.
        const double lbeta_ab = lgamma(a) + lgamma(b) - lgamma(a + b);
        const double front = exp(log(x) * a + log(1.0 - x) * b - lbeta_ab) / a;

        // Use Lentz's algorithm to evaluate the continued fraction.
        T f = 1.0l, c = 1.0l, d = 0.0l;

        for (int i = 0; i <= 200; ++i) {
            int m = i / 2;

            T numerator;
            if (i == 0) {
                // First numerator is 1.0.
                numerator = 1.0l;
            } else if (i % 2 == 0) {
                // Even term.
                numerator =
                    (m * (b - m) * x) / ((a + 2.0 * m - 1.0) * (a + 2.0 * m));
            } else {
                // Odd term.
                numerator = -((a + m) * (a + b + m) * x) /
                            ((a + 2.0 * m) * (a + 2.0 * m + 1));
            }

            // Do an iteration of Lentz's algorithm.
            d = 1.0 + numerator * d;
            if (fabs(d) < TINY)
                d = TINY;
            d = 1.0 / d;
            c = 1.0 + numerator / c;
            if (fabs(c) < TINY)
                c = TINY;

            const T cd = c * d;
            f *= cd;

            // Check for stop.
            if (abs(1.0 - cd) < 1.0e-8) {
                return front * (f - 1.0);
            }
        }

        // Needed more loops, did not converge
        return 1.0 / 0.0;
    }

    /// Incomplete beta function with beta parameter
    template <Floating T1, Floating T2, Floating T3, Floating T4>
    auto betain(T1 x, T2 p, T3 q, T4 beta) {
        //  Check the input arguments.
        if (p <= 0.0 || q <= 0.0) {
            throw std::runtime_error(
                "BETAIN - Fatal error!\nP <= 0.0 or Q <= 0.0\n");
        }

        if (x < 0.0 || 1.0 < x) {
            throw std::runtime_error(
                "BETAIN - Fatal error!\nx < 0.0 or ! < X\n");
        }

        double value = x;

        //  Special cases.
        if (abs(x) < epsilon<T> || abs(x - 1.0) < epsilon<T>) {
            return value;
        }

        // Change tail if necessary and determine S.
        double psq = p + q;
        double cx = 1.0 - x;

        double xx;
        double pp;
        double qq;
        bool indx;
        if (p < psq * x) {
            xx = cx;
            cx = x;
            pp = q;
            qq = p;
            indx = true;
        } else {
            xx = x;
            pp = p;
            qq = q;
            indx = false;
        }

        double term = 1.0;
        double ai = 1.0;
        value = 1.0;
        int ns = static_cast<int>(qq + cx * psq);

        // Use the Soper reduction formula.
        double rx = xx / cx;
        double temp = qq - ai;
        if (ns == 0) {
            rx = xx;
        }

        for (;;) {
            term = term * temp * rx / (pp + ai);
            value = value + term;
            temp = fabs(term);

            constexpr double acu = 0.1E-14;
            if (temp <= acu && temp <= acu * value) {
                value = value *
                        exp(pp * log(xx) + (qq - 1.0) * log(cx) - beta) / pp;

                if (indx) {
                    value = 1.0 - value;
                }
                break;
            }

            ai = ai + 1.0;
            ns = ns - 1;

            if (0 <= ns) {
                temp = qq - ai;
                if (ns == 0) {
                    rx = xx;
                }
            } else {
                temp = psq;
                psq = psq + 1.0;
            }
        }

        return value;
    }
} // namespace scistats

#endif // SCISTATS_BETA_INC_H
