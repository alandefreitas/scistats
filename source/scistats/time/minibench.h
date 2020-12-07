//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_MINIBENCH_H
#define SCISTATS_MINIBENCH_H

#include <scistats/time/tictoc.h>
#include <vector>

namespace scistats {
    template<typename CALLABLE, typename DURATION_TYPE = std::chrono::nanoseconds>
    std::vector<typename DURATION_TYPE::rep> minibench(CALLABLE fn, size_t replicates = 30) {
        std::vector<typename DURATION_TYPE::rep> results(replicates);
        for (size_t i = 0; i < replicates; ++i) {
            auto s = tic<DURATION_TYPE>();
            fn();
            results[i] = toc<DURATION_TYPE>(s);
        }
        return results;
    }
}

#endif //SCISTATS_MINIBENCH_H
