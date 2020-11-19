#include <algorithm>
#include <chrono>
#include <iostream>
#include <matplot/matplot.h>
#include <random>
#include <range/v3/all.hpp>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/stddev.h>
#include <vector>

int main() {
    using namespace scistats;
    using namespace ranges::views;

    // Treatments
    auto algorithms = {1, 2};

    // Instances
    auto problem_sizes =
        iota(1UL, 15UL) | transform([](auto x) { return 1U << x; });

    // Replicates for each combination
    constexpr size_t n_replicates = 30;

    // Results <problem_size,algorithm,time>
    std::vector<std::tuple<size_t, int, double>> results;

    // Random generator for instances
    std::random_device r;
    std::mt19937 g(r());
    std::uniform_int_distribution<int> ud(0, 255);

    // For each replicate
    for (const auto &problem_size : problem_sizes) {
        for (const auto &algorithm : algorithms) {
            for (const auto &replicate_idx : iota(1UL, n_replicates)) {
                // Create problem of size
                std::vector<int> v(problem_size);
                ranges::generate(v, [&]() { return ud(g); });

                // Measure time to sort vector
                auto start_time = std::chrono::high_resolution_clock::now();
                if (algorithm == 1) {
                    ranges::sort(v);
                } else {
                    ranges::stable_sort(v);
                }
                auto end_time = std::chrono::high_resolution_clock::now();

                // Save result
                results.emplace_back(problem_size, algorithm,
                                     (end_time - start_time).count());
            }
        }
    }

    // For each algorithm / problem_size
    for (const auto &algorithm : algorithms) {
        // problem size
        std::vector<double> x = {};
        // algorithm average time
        std::vector<double> y = {};
        // algorithm std dev
        std::vector<double> err = {};
        for (const auto &problem_size : problem_sizes) {
            // Create view with results
            auto is_alg_and_prob = [&](auto rep) {
                return std::get<0>(rep) == problem_size &&
                       std::get<1>(rep) == algorithm;
            };
            auto get_rep_time = [&](auto rep) { return std::get<2>(rep); };
            auto times =
                filter(results, is_alg_and_prob) | transform(get_rep_time);

            // Emplace results in vector for plots
            x.emplace_back(problem_size);
            y.emplace_back(mean(times));
            err.emplace_back(stddev(times));
        }
        // Plot algorithm results
        matplot::hold(true);
        matplot::errorbar(x, y, err)->filled_curve(true);
    }

    matplot::show();

    return 0;
}
