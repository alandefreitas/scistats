//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_GAMMALN_H
#define SCISTATS_GAMMALN_H

// C++
#include <cmath>

// External

// Internal
#include <scistats/common/concepts.h>

namespace scistats {
    /// Natural logarithm of the gamma function
    /// \see http://lib.stat.cmu.edu/apstat/
    template <Floating T>
    T gammaln(T x) {
        return std::lgamma(x);
    }
} // namespace scistats

#endif // SCISTATS_GAMMALN_H
