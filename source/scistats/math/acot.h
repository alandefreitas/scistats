//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_ACOT_H
#define SCISTATS_ACOT_H

#include <cmath>
#include <scistats/common/concepts.h>

namespace scistats {
    /// Inverse cotangent
    template <Floating T>
    T acot(T x) {
        return atan(1.0 / x);
    }
} // namespace scistats

#endif // SCISTATS_ACOT_H
