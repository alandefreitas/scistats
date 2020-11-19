//
// Created by Alan Freitas on 2019-11-21.
//

#ifndef SCISTATS_BAYESIAN_BOOTSTRAP_H
#define SCISTATS_BAYESIAN_BOOTSTRAP_H

#include <functional>
#include <range/v3/algorithm/generate.hpp>
#include <scistats/common/concepts.h>
#include <scistats/common/type_traits.h>

namespace scistats {
    /// \brief Bootstrap tests
    /// \see
    /// https://www.quora.com/In-laymans-terms-what-is-bootstrapping-in-statistics
    /// \see https://www.mathworks.com/help/stats/bootstrp.html
    /// \see https://www.mathworks.com/help/stats/bootci.html
    /// \see
    /// https://www.mathworks.com/help/stats/resampling-techniques.html?s_tid=CRUX_lftnav
    constexpr size_t DEFAULT_BOOTSTRAP_REPLICATES = 1000000;

    /// \brief Bootstrap sampling from a single function with no inputs
    /// This runs a function many times and keeps the results
    /// \param statistic_fn Function that takes no input and returns a value
    /// with a statistic
    /// \param n_replicates Number of times we run the function
    /// \return Vector with n results of the statistic
    template <Callable F>
    auto bootstrap(F statistic_fn,
                   size_t n_replicates = DEFAULT_BOOTSTRAP_REPLICATES) {
        using S = decltype(statistic_fn());
        std::vector<S> data(n_replicates);
        ranges::generate(data.begin(), data.end(), statistic_fn);
        return data;
    }

    /// \brief Bootstrap sampling with a custom function to generate groups of
    /// data This runs a function many times and keeps the results \param
    /// statistic_fn Function that takes a vector of data a returns a
    /// statistic_fn \param range_data_source Function that gives us vectors of
    /// data \param n_replicates Number of times we run the function \return
    /// Vector with n results of the statistic_fn
    template <Callable F1, Callable F2>
    auto bootstrap(F1 statistic_fn, F2 range_data_source,
                   size_t n_replicates = DEFAULT_BOOTSTRAP_REPLICATES) {
        using S2 = decltype(range_data_source());
        using S1 = decltype(statistic_fn(S2{}));
        std::vector<S1> data(n_replicates);
        return bootstrap(
            [&range_data_source, &statistic_fn]() {
                S2 intermediary_data = range_data_source();
                return statistic_fn(intermediary_data);
            },
            n_replicates);
    }

    /// \brief Bootstrap sampling from a function that generates data
    /// This runs a function many times and keeps the results
    /// \param statistic_fn Function that takes a vector of data a returns a
    /// statistic_fn
    /// \param range_data_source Function that gives us data
    /// \param sample_size Sample sizes we get from range_data_source
    /// \param n_replicates
    /// Number of times we run the function \return Vector with n results of the
    /// statistic_fn
    template <typename S, typename I>
    auto bootstrap(std::function<S(std::vector<I>)> statistic_fn,
                   std::function<S()> range_data_source, size_t sample_size,
                   size_t n_replicates = DEFAULT_BOOTSTRAP_REPLICATES) {
        std::vector<S> data(n_replicates);
        return bootstrap(
            [&]() {
                std::vector<S> intermediary_data(sample_size);
                std::generate(data.begin(), data.end(), range_data_source);
                return statistic_fn(data);
            },
            n_replicates);
    }

} // namespace scistats

#endif // SCISTATS_BAYESIAN_BOOTSTRAP_H
