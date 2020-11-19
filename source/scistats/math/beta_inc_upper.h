//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_BETA_INC_UPPER_H
#define SCISTATS_BETA_INC_UPPER_H

// C++
#include <cmath>

// Internal
#include <scistats/common/concepts.h>
#include <scistats/math/abs.h>
#include <scistats/math/beta_inc.h>

namespace scistats {
    /// Incomplete beta function with upper tail
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T1, Floating T2, Floating T3>
    auto beta_inc_upper(T1 x, T2 a, T3 b) {
        return 1.0 - beta_inc(x, a, b);
    }
} // namespace scistats

#endif // SCISTATS_BETA_INC_UPPER_H
