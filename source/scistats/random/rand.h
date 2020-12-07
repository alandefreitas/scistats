//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_RAND_H
#define SCISTATS_RAND_H

#include <scistats/common/concepts.h>
#include <scistats/random/default_generator.h>

namespace scistats {
    template <Floating T>
    T rand(T imin, T imax) {
        return std::uniform_real_distribution<T>(imin,
                                                 imax)(default_generator());
    }

    template <Floating T>
    T rand(T imax) {
        return rand(0, imax);
    }

    template <Floating T>
    T rand() {
        return rand<T>(0, std::numeric_limits<T>::max());
    }

    template <Integer T>
    T rand(T imin, T imax) {
        return std::uniform_int_distribution<T>(imin,
                                                imax)(default_generator());
    }

    template <Integer T>
    T rand(T imax) {
        return rand(0, imax);
    }

    template <Integer T>
    T rand() {
        return rand<T>(0, std::numeric_limits<T>::max());
    }
} // namespace scistats

#endif // SCISTATS_RAND_H
