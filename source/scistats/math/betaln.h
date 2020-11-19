//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_BETALN_H
#define SCISTATS_BETALN_H

// C++
#include <cmath>

// External

// Internal
#include <scistats/common/concepts.h>
#include <scistats/math/gammaln.h>

namespace scistats {
    /// Natural logarithm of the beta function
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T>
    T betaln(T z, T w) {
        return gammaln(z) + gammaln(w) - gammaln(z + w);
    }
} // namespace scistats

#endif // SCISTATS_BETALN_H
