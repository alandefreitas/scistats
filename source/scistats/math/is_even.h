//
// Created by Alan Freitas on 12/4/20.
//

#ifndef SCISTATS_IS_EVEN_H
#define SCISTATS_IS_EVEN_H

#include <scistats/common/concepts.h>

namespace scistats {
    template <Integer T>
    constexpr bool is_even(T v) {
        return !(v & 1);
    }
} // namespace scistats

#endif // SCISTATS_IS_EVEN_H
