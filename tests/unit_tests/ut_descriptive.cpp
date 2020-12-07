#include <boost/ut.hpp>
#include <scistats/descriptive/bounds.h>
#include <scistats/descriptive/cov.h>
#include <scistats/descriptive/max.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/median.h>
#include <scistats/descriptive/min.h>
#include <scistats/descriptive/mode.h>
#include <scistats/descriptive/percentile.h>
#include <scistats/descriptive/stddev.h>
#include <scistats/descriptive/var.h>
#include <vector>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    std::vector<int> x2 = {29, 46, 58, 42, 2,  43, 20, 84, 84, 74,
                           45, 88, 51, 67, 54, 30, 73, 69, 39, 13,
                           16, 88, 45, 24, 22, 64, 77, 87, 77, 84};

    test("Central Tendency") = [&] {
        test("Mean") = [&] {
            expect(mean(x.begin(), x.end()) == 1.91667_f);
            expect(mean(x) == 1.91667_f);
            expect(mean(execution::seq, x) == 1.91667_f);
            expect(mean(execution::par, x) == 1.91667_f);
        };

        test("Median") = [&] {
            expect(median(x) == 2._f);
            expect(median(x2) == 52.5_f);
        };

        test("Percentile") = [&] {
            expect(percentile(x2, 10) == 18._f);
            expect(percentile(x2, 90) == 85.5_f);
        };

        test("Mode") = [&] {
            expect(mode(x) == 2_i);
            expect(mode(std::vector<int>{6, 4, 8, 6}) == 6_i);
        };
    };

    test("Distribution") = [&] {
        test("Min") = [&] {
            expect(min(x) == 0_i);
            expect(min(execution::par, x) == 0_i);

            expect(min(1, 2) == 1_i);
            expect(min(1, 2, 3) == 1_i);
            expect(min(1, 2, 3, 6) == 1_i);
            expect(min(2, 3, 1, 6) == 1_i);
        };

        test("Max") = [&] {
            expect(max(x) == 4_i);
            expect(max(execution::par, x) == 4_i);
            expect(max(1, 2) == 2_i);
            expect(max(1, 2, 3) == 3_i);
            expect(max(1, 2, 3, 6) == 6_i);
            expect(max(2, 6, 1, 3) == 6_i);
        };

        test("Bounds") = [&] {
            expect(bounds(x) == std::pair<int, int>{0, 4});
            expect(bounds(execution::par, x) == std::pair<int, int>{0, 4});
            expect(bounds(1, 2) == std::pair<int, int>{1, 2});
            expect(bounds(1, 2, 3) == std::pair<int, int>{1, 3});
            expect(bounds(1, 2, 3, 6) == std::pair<int, int>{1, 6});
            expect(bounds(2, 6, 1, 3) == std::pair<int, int>{1, 6});
        };

        test("Variance") = [&] {
            expect(var(x) == 1.17424_f);
            expect(var(execution::par, x) == 1.17424_f);
            expect(var(x2) == 663.592_f);
        };

        test("Standard deviation") = [&] {
            expect(stddev(x) == 1.08362_f);
            expect(stddev(execution::par, x) == 1.08362_f);
            expect(stddev(x2) == 25.7603_f);
        };
    };

    test("Correlation") = [&] {
        test("Covariance") = [&] {
            std::vector<int> A = {3, 6, 4};
            std::vector<int> B = {7, 12, -9};
            expect(cov(A, B) == 6.8333_f);
            expect(cov(execution::par, A, B) == 6.8333_f);
        };
    };

    return 0;
}
