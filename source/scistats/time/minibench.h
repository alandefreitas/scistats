//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_MINIBENCH_H
#define SCISTATS_MINIBENCH_H

#include <scistats/time/tictoc.h>
#include <scistats/time/timeit.h>
#include <vector>

namespace scistats {
    /// \brief Run a function repeatedly and store the time duration
    /// \tparam DURATION_TYPE Duration type (default = nanoseconds)
    /// \tparam CALLABLE Function type with no parameters
    /// \param fn Function to be benchmarked
    /// \param replicates Number of iterations (default = 30 as a rule of thumb
    /// for the central limit theorem)
    /// \return Vector with durations in nanoseconds
    template <typename DURATION_TYPE = std::chrono::nanoseconds,
              typename CALLABLE = std::function<void()>>
    std::vector<typename DURATION_TYPE::rep> minibench(CALLABLE fn,
                                                       size_t replicates = 30) {
        std::vector<typename DURATION_TYPE::rep> results(replicates);
        for (size_t i = 0; i < replicates; ++i) {
            results[i] = timeit<DURATION_TYPE, CALLABLE>(fn);
        }
        return results;
    }
} // namespace scistats

#endif // SCISTATS_MINIBENCH_H
