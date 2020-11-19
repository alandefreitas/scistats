//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_XINBTA_H
#define SCISTATS_XINBTA_H

// C++
#include <cmath>
#include <stdexcept>

// External

// Internal
#include <scistats/math/beta_inc.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// Inverse incomplete beta function with alpha parameter
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T1, Floating T2, Floating T3, Floating T4>
    auto xinbta(T1 p, T2 q, T3 beta, T4 alpha) {
        //  Test for admissibility of parameters.
        if (p <= 0.0) {
            throw std::runtime_error("XINBTA - Fatal error!\nP <= 0.0.");
        }

        if (q <= 0.0) {
            throw std::runtime_error("XINBTA - Fatal error!\nQ <= 0.0.");
        }

        if (alpha < 0.0 || 1.0 < alpha) {
            throw std::runtime_error(
                "XINBTA - Fatal error!\nALPHA not between 0 and 1.");
        }

        constexpr double sae = -30.0;
        double fpu = std::pow(10.0, sae);

        //  If the answer is easy to determine, return immediately.
        if (abs(alpha) < epsilon<double>) {
            return 0.0;
        }

        if (abs(alpha-1.0) < epsilon<double>) {
            return 1.0;
        }

        // Change tail if necessary.
        double a;
        double pp;
        double qq;
        bool indx;
        if (0.5 < alpha) {
            a = 1.0 - alpha;
            pp = q;
            qq = p;
            indx = true;
        } else {
            a = alpha;
            pp = p;
            qq = q;
            indx = false;
        }

        //  Calculate the initial approximation.
        double r = sqrt(-log(a * a));

        double y =
            r - (2.30753 + 0.27061 * r) / (1.0 + (0.99229 + 0.04481 * r) * r);

        double s;
        double t;
        double h;
        double w;
        double value;
        if (1.0 < pp && 1.0 < qq) {
            r = (y * y - 3.0) / 6.0;
            s = 1.0 / (pp + pp - 1.0);
            t = 1.0 / (qq + qq - 1.0);
            h = 2.0 / (s + t);
            w = y * sqrt(h + r) / h -
                (t - s) * (r + 5.0 / 6.0 - 2.0 / (3.0 * h));
            value = pp / (pp + qq * exp(w + w));
        } else {
            r = qq + qq;
            t = 1.0 / (9.0 * qq);
            t = r * pow(1.0 - t + y * sqrt(t), 3);

            if (t <= 0.0) {
                value = 1.0 - exp((log((1.0 - a) * qq) + beta) / qq);
            } else {
                t = (4.0 * pp + r - 2.0) / t;

                if (t <= 1.0) {
                    value = exp((log(a * pp) + beta) / pp);
                } else {
                    value = 1.0 - 2.0 / (t + 1.0);
                }
            }
        }

        //  Solve for X by a modified Newton-Raphson method,
        //  using the function BETAIN.
        r = 1.0 - pp;
        t = 1.0 - qq;
        double yprev = 0.0;
        double sq = 1.0;
        double prev = 1.0;

        if (value < 0.0001) {
            value = 0.0001;
        }

        if (0.9999 < value) {
            value = 0.9999;
        }

        int iex = static_cast<int>(
            std::max(-5.0 / pp / pp - 1.0 / pow(a, 0.2) - 13.0, sae));
        double acu = pow(10.0, iex);

        //  Iteration loop.
        double adj;
        double g;
        double tx;
        double xin;
        for (;;) {
            y = betain(value, pp, qq, beta);

            xin = value;
            y = (y - a) * exp(beta + r * log(xin) + t * log(1.0 - xin));

            if (y * yprev <= 0.0) {
                prev = std::max(sq, fpu);
            }

            g = 1.0;

            for (;;) {
                for (;;) {
                    adj = g * y;
                    sq = adj * adj;

                    if (sq < prev) {
                        tx = value - adj;

                        if (0.0 <= tx && tx <= 1.0) {
                            break;
                        }
                    }
                    g = g / 3.0;
                }

                //  Check whether the current estimate is acceptable.
                //  The change "VALUE = TX" was suggested by Ivan Ukhov.
                if (prev <= acu || y * y <= acu) {
                    value = tx;
                    if (indx) {
                        value = 1.0 - value;
                    }
                    return value;
                }

                if (abs(tx) > epsilon<double> && abs(tx-1.) > epsilon<double>) {
                    break;
                }

                g = g / 3.0;
            }

            constexpr double epsilon = 0.0000001;
            if (fabs(tx - value) < epsilon) {
                break;
            }

            value = tx;
            yprev = y;
        }

        if (indx) {
            value = 1.0 - value;
        }

        return value;
    }
} // namespace scistats

#endif // SCISTATS_XINBTA_H
