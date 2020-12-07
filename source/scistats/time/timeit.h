//
// Created by Alan Freitas on 12/7/20.
//

#ifndef SCISTATS_TIMEIT_H
#define SCISTATS_TIMEIT_H

#include <functional>
#include <scistats/time/tictoc.h>

namespace scistats {
    template <typename DURATION_TYPE = std::chrono::nanoseconds,
              typename CALLABLE = std::function<void()>>
    typename DURATION_TYPE::rep timeit(const CALLABLE &fn) {
        auto s = tic<DURATION_TYPE>();
        fn();
        return toc<DURATION_TYPE>(s);
    }
} // namespace scistats

#endif // SCISTATS_TIMEIT_H
