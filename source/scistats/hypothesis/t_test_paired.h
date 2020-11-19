//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_T_TEST_PAIRED_H
#define SCISTATS_T_TEST_PAIRED_H

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
#include <scistats/distribution/students_t.h>
#include <scistats/hypothesis/tail.h>
#include <scistats/math/constants.h>

namespace scistats {
    /// \brief Paired-sample t-test
    /// \tparam T1 Type of first range
    /// \tparam T2  Type of second range
    /// \param x First range
    /// \param y Second range
    /// \param tail Tail type
    /// \param mu Expected difference between first and second range in the null
    /// hypothesis
    /// \return p-value
    template <Range T1, Range T2>
    double t_test_paired(const T1 &x, const T2 &y,
                         tail_type tail = tail_type::two_tailed,
                         double mu = 0.0) {
        if (x.size() != y.size()) {
            throw std::logic_error("Input sizes of X and Y do not match");
        }

        // t = x - y
        std::vector<value_type<T1>> t(x.begin(), x.end());
        for (size_t i = 0; i < x.size(); ++i) {
            t[i] -= y[i];
        }

        return t_test(t, mu, tail);
    }

} // namespace scistats
#endif // SCISTATS_T_TEST_PAIRED_H
