//
// Created by Alan Freitas on 17/11/20.
//

#ifndef SCISTATS_T_TEST_H
#define SCISTATS_T_TEST_H

// C++
#include <algorithm>
#include <cmath>

// External
#include <async++.h>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/count_if.hpp>
#include <range/v3/view/concat.hpp>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/stddev.h>
#include <scistats/distribution/students_t.h>
#include <scistats/hypothesis/tail.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// \brief One-sample t-test
    template <Range T>
    double t_test(const T &x, double mu = 0.0,
                  tail_type tail = tail_type::two_tailed) {
        size_t n_nans = ranges::count(x, NaN<typename T::value_type>);
        if (n_nans) {
            throw std::logic_error("Cannot run t-test with NaNs in the data");
        }

        size_t n_infs =
            ranges::count_if(x, [](auto v) { return std::isinf(v); });
        if (n_infs) {
            throw std::logic_error(
                "Cannot run t-test with infinity in the data");
        }

        size_t sample_size = x.size() - n_nans;
        auto df = static_cast<double>(sample_size - 1);
        double xmean = mean(x);
        double sdpop = stddev(x, xmean);
        double ser = sdpop / std::sqrt(sample_size);
        double tval = (xmean - mu) / ser;

        // Compute the p-value for the test
        switch (tail) {
        case tail_type::two_tailed:
            return 2. * t_cdf(-abs(tval), df);
            break;
        case tail_type::right_tail:
            return t_cdf(-tval, df);
            break;
        case tail_type::left_tail:
            return t_cdf(tval, df);
            break;
        }
        return NaN<double>;
    }

    /// \brief Two-sample t-test
    template <Range T1, Range T2>
    double t_test(const T1 &x, const T2 &y, int equal_variance = true,
                  tail_type tail = tail_type::two_tailed) {
        size_t n_nans =
            ranges::count(ranges::views::concat(x, y), NaN<value_type<T1>>);
        if (n_nans) {
            throw std::logic_error("Cannot run t-test with NaNs in the data");
        }

        size_t n_infs = ranges::count_if(ranges::views::concat(x, y),
                                         [](auto v) { return std::isinf(v); });
        if (n_infs) {
            throw std::logic_error(
                "Cannot run t-test with infinity in the data");
        }

        const size_t nx = x.size();
        const size_t ny = y.size();
        double mean_x = mean(x);
        double mean_y = mean(y);
        double s2x = var(x, mean_x);
        double s2y = var(y, mean_y);
        double difference = mean_x - mean_y;

        double dfe = 0;
        double ratio = 0;
        if (equal_variance) {
            dfe = nx + ny - 2;
            double s_pooled = sqrt(((nx - 1) * s2x + (ny - 1) * s2y) / dfe);
            double se = s_pooled * sqrt(1. / nx + 1. / ny);
            ratio = difference / se;
        } else {
            double s2xbar = s2x / nx;
            double s2ybar = s2y / ny;
            dfe = pow((s2xbar + s2ybar), 2) /
                  (pow(s2xbar, 2) / (nx - 1) + pow(s2ybar, 2) / (ny - 1));
            double se = sqrt(s2xbar + s2ybar);
            ratio = difference / se;
            if (abs(se) < epsilon<double>) {
                dfe = 1;
            }
        }

        // Compute the p-value for the test
        switch (tail) {
        case tail_type::two_tailed:
            return 2 * t_cdf(-abs(ratio), dfe);
        case tail_type::right_tail:
            return t_cdf(-ratio, dfe);
        case tail_type::left_tail:
            return t_cdf(ratio, dfe);
        }
        return NaN<double>;
    }

} // namespace scistats

#endif // SCISTATS_T_TEST_H
