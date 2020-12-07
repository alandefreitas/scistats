#include <scistats/time/tictoc.h>
#include <scistats/time/minibench.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/stddev.h>
#include <matplot/matplot.h>
#include <random>

int main() {
    using namespace scistats;
    using namespace matplot;

    auto s = tic();
    std::cout << "Hello world: " << s << " nanoseconds since epoch" << std::endl;
    auto t = toc(s);
    std::cout << "Printing s took: " << t << " nanoseconds" << std::endl;

    constexpr size_t max_vector_size = 1000;
    std::random_device r;
    std::mt19937 g(r());
    std::vector<double> xs;
    std::vector<double> means_1;
    std::vector<double> means_2;
    std::vector<double> stddevs_1;
    std::vector<double> stddevs_2;
    for (size_t i = 10; i < max_vector_size; ++i) {
        std::vector<int> v(i);
        std::iota(v.begin(), v.end(), 0);
        std::uniform_int_distribution<size_t> d(0, i - 1);

        auto t1 = minibench([&]() {
            auto it = std::find(v.begin(), v.end(), v[d(g)]);
        });

        auto t2 = minibench([&]() {
            auto ok = std::binary_search(v.begin(), v.end(), v[d(g)]);
        });

        xs.emplace_back(static_cast<double>(i));
        means_1.emplace_back(static_cast<double>(mean(t1)));
        means_2.emplace_back(static_cast<double>(mean(t2)));
        stddevs_1.emplace_back(static_cast<double>(stddev(t1)));
        stddevs_2.emplace_back(static_cast<double>(stddev(t2)));
    }

    auto ax = matplot::gca();
    ax->errorbar(xs, means_1, stddevs_1)->filled_curve(true);
    ax->hold(true);
    ax->errorbar(xs, means_2, stddevs_2)->filled_curve(true);
    ax->legend({"Sequential Search", "Binary Search"});
    matplot::show();
}
