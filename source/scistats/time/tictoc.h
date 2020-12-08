//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_TICTOC_H
#define SCISTATS_TICTOC_H

#include <chrono>
#include <scistats/common/concepts.h>

namespace scistats {
    /// \brief Get current time point as an integer with nanoseconds since epoch
    /// \tparam DURATION_TYPE Duration type (default = nanoseconds)
    /// \return Current time
    template <typename DURATION_TYPE = std::chrono::nanoseconds>
    typename DURATION_TYPE::rep tic() {
        auto tp = std::chrono::high_resolution_clock::now();
        auto dur = tp.time_since_epoch();
        if constexpr (std::is_same_v<decltype(dur), DURATION_TYPE>) {
            return dur.count();
        } else {
            auto dur2 = std::chrono::duration_cast<DURATION_TYPE>(dur);
            return dur2.count();
        }
    }

    /// \brief Get time difference from tic_time to current time in nanoseconds
    /// \tparam DURATION_TYPE Duration type (default = nanoseconds)
    /// \param tic_time Initial time point
    /// \return Duration from tic_time in nanoseconds
    template <typename DURATION_TYPE = std::chrono::nanoseconds>
    double toc(typename DURATION_TYPE::rep tic_time) {
        typename DURATION_TYPE::rep toc_time = tic();
        return toc_time - tic_time;
    }

} // namespace scistats

#endif // SCISTATS_TICTOC_H
