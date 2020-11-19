//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_T_TEST_INTERVAL_H
#define SCISTATS_T_TEST_INTERVAL_H

// C++
#include <algorithm>
#include <cmath>

// External
#include <async++.h>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/count_if.hpp>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/stddev.h>
#include <scistats/descriptive/var.h>
#include <scistats/distribution/students_t.h>
#include <scistats/hypothesis/tail.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// \brief One-sample t-test interval
    template <Range T>
    auto t_test_interval(T &x, double alpha = 0.05,
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
        double crit = 0;

        // Compute the confidence interval for the test
        switch (tail) {
        case tail_type::two_tailed: {
            crit = t_inv((1 - alpha / 2), df) * ser;
            return std::make_pair(xmean - crit, xmean + crit);
        }
        case tail_type::right_tail: {
            crit = t_inv(1 - alpha, df) * ser;
            return std::make_pair(xmean - crit,
                                  std::numeric_limits<double>::infinity());
        }
        case tail_type::left_tail: {
            crit = t_inv(1 - alpha, df) * ser;
            return std::make_pair(-std::numeric_limits<double>::infinity(),
                                  xmean + crit);
        }
        }
        return std::make_pair(NaN<double>,NaN<double>);
    }

    /// \brief Two-sample t-test interval
    template <Range T1, Range T2>
    std::pair<double, double>
    t_test_interval(const T1 &x, const T2 &y, double alpha = 0.05,
                    int equal_variance = true,
                    tail_type tail = tail_type::two_tailed) {
        const size_t nx = x.size();
        const size_t ny = y.size();
        double mean_x = mean(x);
        double mean_y = mean(y);
        double s2x = var(x, mean_x);
        double s2y = var(y, mean_y);
        double difference = mean_x - mean_y;

        double dfe = 0, se = 0;
        if (equal_variance) {
            dfe = nx + ny - 2;
            double s_pooled = sqrt(((nx - 1) * s2x + (ny - 1) * s2y) / dfe);
            se = s_pooled * sqrt(1. / nx + 1. / ny);
        } else {
            double s2xbar = s2x / nx;
            double s2ybar = s2y / ny;
            dfe = pow((s2xbar + s2ybar), 2) /
                  (pow(s2xbar, 2) / (nx - 1) + pow(s2ybar, 2) / (ny - 1));
            se = sqrt(s2xbar + s2ybar);
            if (abs(se) < epsilon<double>) {
                dfe = 1;
            }
        }

        switch (tail) {
        case tail_type::two_tailed: {
            double spread = t_inv(1 - alpha / 2, dfe) * se;
            return std::make_pair(difference - spread, difference + spread);
        }
        case tail_type::right_tail: {
            double spread = t_inv(1 - alpha, dfe) * se;
            return std::make_pair(difference - spread,
                                  std::numeric_limits<double>::infinity());
        }
        case tail_type::left_tail: {
            double spread = t_inv(1 - alpha, dfe) * se;
            return std::make_pair(-std::numeric_limits<double>::infinity(),
                                  difference + spread);
        }
        }
        return std::make_pair(NaN<double>,NaN<double>);
    }

} // namespace scistats

#endif // SCISTATS_T_TEST_INTERVAL_H
