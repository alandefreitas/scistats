//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_COT_H
#define SCISTATS_COT_H

// C++
#include <cmath>

// External

// Internal
#include <scistats/common/concepts.h>

namespace scistats {
    /// Cotangent
    template <Floating T>
    T cot(T x) {
        return 1.0 / tan(x);
    }

} // namespace scistats

#endif // SCISTATS_COT_H
