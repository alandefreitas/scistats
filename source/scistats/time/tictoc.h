//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_TICTOC_H
#define SCISTATS_TICTOC_H

#include <chrono>
#include <scistats/common/concepts.h>

namespace scistats {
    template <typename DURATION_TYPE = std::chrono::nanoseconds>
    typename DURATION_TYPE::rep tic() {
        std::chrono::high_resolution_clock::time_point tp =
            std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point::duration dur =
            tp.time_since_epoch();
        DURATION_TYPE dur2 = std::chrono::duration_cast<DURATION_TYPE>(dur);
        return dur2.count();
    }

    template <typename DURATION_TYPE = std::chrono::nanoseconds>
    double toc(typename DURATION_TYPE::rep tic_time) {
        typename DURATION_TYPE::rep toc_time = tic();
        return toc_time - tic_time;
    }
} // namespace scistats

#endif // SCISTATS_TICTOC_H
