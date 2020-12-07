//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_DEFAULT_GENERATOR_H
#define SCISTATS_DEFAULT_GENERATOR_H

#include <random>

namespace scistats {
    inline uint64_t default_seed() {
        static uint64_t seed =
            static_cast<unsigned int>(std::random_device()()) |
            static_cast<unsigned int>(std::chrono::high_resolution_clock::now()
                                          .time_since_epoch()
                                          .count());
        return seed;
    }

    inline std::mt19937 &default_generator() {
        static std::mt19937 g(default_seed());
        return g;
    }
} // namespace scistats

#endif // SCISTATS_DEFAULT_GENERATOR_H
