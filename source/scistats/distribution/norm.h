//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_NORM_H
#define SCISTATS_NORM_H

#include <cmath>
#include <scistats/common/concepts.h>
#include <scistats/math/constants.h>
#include <scistats/math/erfinv.h>

namespace scistats {
    /// \brief Normal probability density function
    template <Floating T>
    T norm_pdf(T x, T mu = T{0.0}, T sigma = T{1.0}) {
        const T variance = std::pow(sigma, 2.0);
        return (1.0 / (sqrt(2.0 * pi<T>() * variance))) *
               exp(-(std::pow(x - mu, 2.0) / (2 * variance)));
    }

    /// \brief Normal cumulative distribution function
    template <Floating T>
    T norm_cdf(T x, T mu = 0.0, T std_dev = 1.0) {
        return 0.5 * (1.0 + erf((x - mu) / (std_dev * sqrt(2.0))));
    }

    /// \brief Normal inverse cumulative distribution function
    template <Floating T>
    T norm_inv(T p, T mu = 0.0, T sigma = 1.0) {
        /* fails on GCC9 */
        return mu + sigma * std::sqrt(2.0) * erfinv(2.0 * p - 1.0);
    }
} // namespace scistats
#endif // SCISTATS_NORM_H
