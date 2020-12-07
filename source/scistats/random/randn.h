//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_RANDN_H
#define SCISTATS_RANDN_H

#include <scistats/random/default_generator.h>
#include <scistats/common/concepts.h>
#include <scistats/common/type_traits.h>

namespace scistats {
    template<Floating T>
    T randn(T mean, T stddev) {
        return std::normal_distribution<T>(mean, stddev)(default_generator());
    }

    template<Floating T>
    T randn(T stddev) {
        return randn(0, stddev);
    }

    template<Floating T>
    T randn() {
        return randn<T>(0, std::numeric_limits<T>::max());
    }

    template<Integer T>
    T randn(T mean, T stddev) {
        return static_cast<T>(std::round(
                std::normal_distribution<promote<T>>(static_cast<promote<T>>(mean), static_cast<promote<T>>(stddev))(
                        default_generator())));
    }

    template<Integer T>
    T randn(T stddev) {
        return randn(0, stddev);
    }

    template<Integer T>
    T randn() {
        return randn<T>(0, std::numeric_limits<T>::max());
    }

}

#endif //SCISTATS_RANDN_H
