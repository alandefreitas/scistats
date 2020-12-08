//
// Created by Alan Freitas on 12/4/20.
//

#ifndef SCISTATS_IS_ODD_H
#define SCISTATS_IS_ODD_H

#include <scistats/common/concepts.h>

namespace scistats {
    template <Integer T>
    constexpr bool is_odd(T v) {
        return v & 1;
    }
} // namespace scistats

#endif // SCISTATS_IS_ODD_H
