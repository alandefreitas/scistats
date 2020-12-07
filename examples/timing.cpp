#include <scistats/time/tictoc.h>
#include <scistats/time/timeit.h>
#include <scistats/time/minibench.h>
#include <scistats/random/randi.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/percentile.h>
#include <scistats/hypothesis/t_test.h>
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

    double vt = timeit([&]() {
        std::vector<int> x(max_vector_size);
    });
    std::cout << "Creating vector takes " << vt << " nanoseconds" << std::endl;

    std::vector<double> xs;
    std::vector<double> means_1;
    std::vector<double> means_2;
    std::vector<double> y_neg_delta_1;
    std::vector<double> y_pos_delta_1;
    std::vector<double> y_neg_delta_2;
    std::vector<double> y_pos_delta_2;
    std::vector<double> ps;
    for (size_t i = 10; i < max_vector_size; ++i) {
        std::vector<int> v(i);
        std::iota(v.begin(), v.end(), 0);

        auto t1 = minibench([&]() {
            auto it = std::find(v.begin(), v.end(), v[randi(0, i - 1)]);
        });

        auto t2 = minibench([&]() {
            auto ok = std::binary_search(v.begin(), v.end(), v[randi(0, i - 1)]);
        });

        xs.emplace_back(static_cast<double>(i));
        means_1.emplace_back(static_cast<double>(mean(t1)));
        means_2.emplace_back(static_cast<double>(mean(t2)));
        y_neg_delta_1.emplace_back(means_1.back() - static_cast<double>(percentile(t1, 25)));
        y_pos_delta_1.emplace_back(static_cast<double>(percentile(t1, 75)) - means_1.back());
        y_neg_delta_2.emplace_back(means_2.back() - static_cast<double>(percentile(t2, 25)));
        y_pos_delta_2.emplace_back(static_cast<double>(percentile(t2, 75)) - means_2.back());
        ps.emplace_back(t_test(t1, t2, false));
    }

    auto ax = matplot::gca();
    ax->errorbar(xs, means_1, y_neg_delta_1, y_pos_delta_1, {}, {})->filled_curve(true);
    ax->hold(true);
    ax->errorbar(xs, means_2, y_neg_delta_2, y_pos_delta_2, {}, {})->filled_curve(true);

    ax->plot(xs, ps)->use_y2(true);
    std::cout << "ps: " << ranges::views::all(ps) << std::endl;
    ax->legend({"Sequential Search", "Binary Search", "p-value"});
    matplot::show();
}
