//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_RANDI_H
#define SCISTATS_RANDI_H

#include <scistats/common/concepts.h>
#include <scistats/random/default_generator.h>

namespace scistats {
    template <Integer T>
    T randi(T imin, T imax) {
        return std::uniform_int_distribution<T>(imin,
                                                imax)(default_generator());
    }

    template <Integer T>
    T randi(T imax) {
        return randi(0, imax);
    }

    template <Integer T>
    T randi() {
        return randi<T>(0, std::numeric_limits<T>::max());
    }

    template <Floating T>
    T randi(T imin, T imax) {
        return std::round(
            std::uniform_real_distribution<T>(imin, imax)(default_generator()));
    }

    template <Floating T>
    T randi(T imax) {
        return randi(0, imax);
    }

    template <Floating T>
    T randi() {
        return randi<T>(0, std::numeric_limits<T>::max());
    }
} // namespace scistats

#endif // SCISTATS_RANDI_H
