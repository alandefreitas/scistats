#include <boost/ut.hpp>
#include <range/v3/algorithm/transform.hpp>
#include <range/v3/view/all.hpp>
#include <scistats/hypothesis/t_test.h>
#include <scistats/hypothesis/t_test_interval.h>
#include <scistats/hypothesis/t_test_paired.h>
#include <vector>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    test("T Test") = [&] {
        std::vector<double> x = {29, 46, 58, 42, 2,  43, 20, 84, 84, 74,
                                 45, 88, 51, 67, 54, 30, 73, 69, 39, 13,
                                 16, 88, 45, 24, 22, 64, 77, 87, 77, 84};

        test("One sample") = [&] {
            expect(t_test(x, 50) == 0.506084_d);
            expect(t_test(x, 53) == 0.971974_d);
            expect(t_test(x, 56) == 0.551569_d);
            auto p = t_test_interval(x);
            expect(p.first == 43.5476_d);
            expect(p.second == 62.7857_d);
        };

        std::vector<double> x_paired(x.size());
        int i = 0;
        ranges::transform(x, x_paired.begin(),
                          [&](const double &v) { return v - 5 + i++ % 5; });

        test("Paired-sample") = [&] {
            expect(abs(t_test_paired(x, x_paired) - 2.96655e-12) == 0._d);
        };

        test("Two-sample") = [&] {
            expect(t_test(x, x_paired, true) == 0.653767_d);
            const std::pair<double, double> &p =
                t_test_interval(x, x_paired, 0.05, true);
            expect(p.first == -10.3192_d);
            expect(p.second == 16.3192_d);
        };
    };

    return 0;
}
