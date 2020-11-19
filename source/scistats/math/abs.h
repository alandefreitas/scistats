//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_ABS_H
#define SCISTATS_ABS_H

#include <cmath>
#include <scistats/common/concepts.h>

namespace scistats {
    template <typename T>
    T abs(T x) {
        return std::abs(x);
    }

    template <Floating T>
    T abs(T x) {
        return std::fabs(x);
    }
} // namespace scistats

#endif // SCISTATS_ABS_H
