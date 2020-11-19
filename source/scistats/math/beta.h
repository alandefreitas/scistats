//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_BETA_H
#define SCISTATS_BETA_H

// C++
#include <cmath>

// Internal
#include <scistats/math/betaln.h>

namespace scistats {
    /// Beta function
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T>
    T beta(T z, T w) {
        return exp(betaln(z, w));
    }
} // namespace scistats

#endif // SCISTATS_BETA_H
