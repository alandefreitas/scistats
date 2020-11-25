//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_STUDENTS_T_H
#define SCISTATS_STUDENTS_T_H

#include <cmath>
#include <scistats/common/concepts.h>
#include <scistats/common/type_traits.h>
#include <scistats/distribution/norm.h>
#include <scistats/math/abs.h>
#include <scistats/math/acot.h>
#include <scistats/math/beta_inc.h>
#include <scistats/math/beta_inc_inv.h>
#include <scistats/math/beta_inc_upper.h>
#include <scistats/math/betaln.h>
#include <scistats/math/constants.h>
#include <scistats/math/tgamma.h>

namespace scistats {
    /// \brief Student's t probability density function
    template <Floating T1, FloatingOrInteger T2>
    T1 t_pdf(T1 x, T2 df) {
        const auto term1_numerator = tgamma((df + T2{1.l}) / T2{2.0l});
        const auto term1_denominator =
            (sqrt(df * pi<T1>) * tgamma(df / T2{2.}));
        const auto term1 = term1_numerator / term1_denominator;
        const auto term2_base = 1.0 + x * x / df;
        const auto term2_exponent = -((df + 1.0) / 2.0);
        const auto term2 = std::pow(term2_base, term2_exponent);
        return term1 * term2;
    }

    /// \brief Student's t cumulative distribution function
    template <Floating T1, FloatingOrInteger T2>
    T1 t_cdf(T1 x, T2 v) {
        // after v > 1e7, we consider this is a normal distribution
        constexpr T2 normal_cutoff = 1e7;

        // error case
        if (v <= 0) {
            return NaN<T1>;
        }

        // most trivial case
        else if (abs(x) < epsilon<T1>) {
            return 0.5;
        }

        // normal distribution if v is very large
        else if (v > normal_cutoff) {
            return norm_cdf(x);
        }

        // cauchy distribution if v == 1
        else if (abs(v - 1) < epsilon<T2>) {
            // For x > 0, F(x) = 1 - F(-|x|).
            bool xpos = x > 0;
            // Special case for Cauchy distribution.  See Devroye pages 29 and
            // 450. Note that instead of the usual Cauchy formula (atan x)/pi +
            // 0.5, we use acot(-x), which is equivalent and avoids roundoff
            // error.
            return xpos + acot(-x) / pi<T1>;
        }

        // general case
        else {
            // General case: first compute F(-|x|) < .5, the lower tail.
            // See Abramowitz and Stegun, formulas and 26.7.1/26.5.27 and 26.5.2
            // For small v, form v/(v+x^2) to maintain precision
            T1 xsq = x * x;
            T1 p = NaN<T1>;

            if (v < xsq) {
                p = beta_inc(v / (v + xsq), v / 2.0, 0.5) / 2.;
            }
            // For large v, form x^2/(v+x^2) to maintain precision
            else {
                p = beta_inc_upper(xsq / (v + xsq), 0.5, v / 2.) / 2.;
            }

            // For x > 0, F(x) = 1 - F(-|x|).
            bool xpos = x > 0;
            if (xpos) {
                // p < .5, cancellation not a problem
                p = 1. - p;
            }
            return p;
        }
    }

    /// \brief Student's t inverse cumulative distribution function
    template <Floating T1, FloatingOrInteger T2>
    T1 t_inv(T1 p, T2 v) {
        // The inverse cdf of 0 is -Inf, and the inverse cdf of 1 is Inf.
        if (abs(p) <= epsilon<T1> && v > 0) {
            return -inf<T1>;
        }

        if (abs(p - 1) <= epsilon<T1> && v > 0) {
            return inf<T1>;
        }

        // invalid input
        if (p < 0 || p > 1 || v <= 0) {
            return NaN<T1>;
        }

        // Invert the Cauchy distribution explicitly
        if (abs(v - 1) <= epsilon<T2>) {
            return tan(pi<T1> * (p - 0.5));
        }

            // For small d.f., call betaincinv which uses Newton's method
        else if (v < 1000) {
            T1 q = p - .5;
            T2 df = v;
            bool t = (abs(q) < .25);
            T1 z = 0.0;
            T1 oneminusz = 0.0;
            if (t) {
                // for z close to 1, compute 1-z directly to avoid roundoff
                oneminusz = beta_inc_inv(2. * abs(q), 0.5, df / 2.);
                z = 1. - oneminusz;
            }
            // (abs(q) >= .25);
            t = !t;
            if (t) {
                z = beta_inc_inv_upper(2. * abs(q), df / 2., 0.5);
                oneminusz = 1. - z;
            }
            T1 sign = (q > 0) ? 1 : (q < 0) ? -1 : 0;
            return sign * sqrt(df * (oneminusz / z));
        }
        // For large d.f., use Abramowitz & Stegun formula 26.7.5
        else {
            T1 xn = norm_inv(p);
            T2 df = v;
            return xn + (pow(xn, 3) + xn) / (4 * df) +
                   (5. * pow(xn, 5.) + 16. * pow(xn, 3.) + 3. * xn) /
                       (96. * pow(df, 2)) +
                   (3. * pow(xn, 7.) + 19. * pow(xn, 5.) + 17. * pow(xn, 3.) -
                    15. * xn) /
                       (384. * pow(df, 3.)) +
                   (79. * pow(xn, 9.) + 776. * pow(xn, 7.) +
                    1482 * pow(xn, 5.) - 1920 * pow(xn, 3.) - 945 * xn) /
                       (92160 * pow(df, 4.));
        }
    }
} // namespace scistats

#endif // SCISTATS_STUDENTS_T_H
