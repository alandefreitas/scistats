#include <benchmark/benchmark.h>
#include <numeric>
#include <scistats/descriptive/mean.h>
#include <vector>

std::vector<double> create_vector(size_t n) {
    std::vector<double> v(n);
    std::iota(v.begin(), v.end(), 0.);
    return v;
}

void mean_sequential(benchmark::State &state) {
    auto x = create_vector(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(scistats::mean(scistats::execution::seq, x));
        benchmark::ClobberMemory();
    }
}
// Register the function as a benchmark
BENCHMARK(mean_sequential)->Range(8, 8U << 15U);

// Define another benchmark
void mean_parallel(benchmark::State &state) {
    auto x = create_vector(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(scistats::mean(scistats::execution::par, x));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(mean_parallel)->Range(8, 8U << 15U);

BENCHMARK_MAIN();