//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_MINIBENCH_H
#define SCISTATS_MINIBENCH_H

#include <scistats/time/tictoc.h>
#include <scistats/time/timeit.h>
#include <vector>

namespace scistats {
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
