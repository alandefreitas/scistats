//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_BETA_INC_INV_H
#define SCISTATS_BETA_INC_INV_H

#include <cmath>
#include <scistats/math/betaln.h>
#include <scistats/math/xinbta.h>

namespace scistats {
    /// Inverse incomplete beta function
    /// \see http://lib.stat.cmu.edu/apstat/
    inline double beta_inc_inv(double p, double a, double b) {
        return xinbta(a, b, betaln(a, b), p);
    }

    /// Inverse incomplete beta function upper tail
    /// \see http://lib.stat.cmu.edu/apstat/
    inline double beta_inc_inv_upper(double p, double a, double b) {
        return beta_inc_inv(1 - p, a, b);
    }

} // namespace scistats

#endif // SCISTATS_BETA_INC_INV_H
