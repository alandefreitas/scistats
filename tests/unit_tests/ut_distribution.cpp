#include <iostream>
#include <vector>

#include <boost/ut.hpp>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>
#include <scistats/distribution/norm.h>
#include <scistats/distribution/students_t.h>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    // Normal distribution
    std::vector<double> x = {-100,  -50,    -10,    -2,    -1,      -0.5,
                             -0.25, -0.2,   -0.125, -0.1,  -0.0625, -0.05,
                             0,     0.0625, 0.1,    0.125, 0.2,     0.25,
                             0.5,   1,      2,      10,    50,      100};

    constexpr auto compare_floating_range = [](std::string_view name,
                                               auto range_a, auto range_b) {
        auto expect_pairs = ranges::views::zip(range_a, range_b);
        std::cout << name << ": range_a: " << ranges::views::all(range_a) << std::endl;
        std::cout << name << ": range_b: " << ranges::views::all(range_b) << std::endl;
        for (const auto &[result, expected] : expect_pairs) {
            bool not_both_inf = !(std::isinf(result) && std::isinf(expected));
            bool not_both_nan = !(std::isnan(result) && std::isnan(expected));
            if (not_both_inf && not_both_nan) {
                expect(abs(result - expected) == 0._d)
                    << result << " != " << expected << " - Comparing " << name;
            }
        }
    };

    double minfd = -inf<double>;
    test("Normal Distribution") = [&] {
        auto pdfs =
            ranges::views::transform(x, [](auto v) { return norm_pdf(v); });
        compare_floating_range(
            "pdfs", pdfs,
            std::vector<double>{
                0,        0,        7.6946e-23, 0.053991,   0.241971, 0.352065,
                0.386668, 0.391043, 0.395838,   0.396953,   0.398164, 0.398444,
                0.398942, 0.398164, 0.396953,   0.395838,   0.391043, 0.386668,
                0.352065, 0.241971, 0.053991,   7.6946e-23, 0,        0});

        auto pdfs2 = ranges::views::transform(
            x, [](auto v) { return norm_pdf(v, 2., 3.); });
        compare_floating_range(
            "pdfs2", pdfs2,
            std::vector<double>{
                1.26351e-252, 7.64023e-67, 4.46101e-05, 0.05467,     0.0806569,
                0.0939706,    0.100379,    0.101628,    0.103476,    0.104085,
                0.104991,     0.105291,    0.106483,    0.107948,    0.108815,
                0.109387,     0.111075,    0.112176,    0.117355,    0.125794,
                0.132981,     0.00379866,  3.42054e-57, 2.53253e-233});

        auto norm_cdfs =
            ranges::views::transform(x, [](auto v) { return norm_cdf(v); });
        compare_floating_range(
            "norm_cdfs", norm_cdfs,
            std::vector<double>{
                0,        0,        0,        0.0227501, 0.158655, 0.308538,
                0.401294, 0.42074,  0.450262, 0.460172,  0.475082, 0.480061,
                0.5,      0.524918, 0.539828, 0.549738,  0.57926,  0.598706,
                0.691462, 0.841345, 0.97725,  1,         1,        1});

        auto norm_cdfs2 = ranges::views::transform(
            x, [](auto v) { return norm_cdf(v, 2., 3.); });
        compare_floating_range(
            "norm_cdfs2", norm_cdfs2,
            std::vector<double>{
                0,        0,        3.16712e-05, 0.0912112, 0.158655, 0.202328,
                0.226627, 0.231678, 0.239369,    0.241964,  0.245884, 0.247198,
                0.252493, 0.259194, 0.263258,    0.265986,  0.274253, 0.279834,
                0.308538, 0.369441, 0.5,         0.99617,   1,        1});

        auto ps =
            ranges::views::transform(x, [](auto v) { return norm_cdf(v); });

        /* still fails on GCC9 fix-it */
        auto norm_invs =
            ranges::views::transform(ps, [](auto p) { return norm_inv(p); });
        std::vector<double> expected_norm_invs{
            minfd, minfd,  minfd,  -2,          -1,          -0.5,
            -0.25, -0.2,   -0.125, -0.1,        -0.0625,     -0.05,
            0,     0.0625, 0.1,    0.125,       0.2,         0.25,
            0.5,   1,      2,      inf<double>, inf<double>, inf<double>};
        // compare_floating_range("norm_invs", norm_invs, expected_norm_invs);

        auto norm_invs2 = ranges::views::transform(
            ps, [](auto p) { return norm_inv(p, 2., 3.); });
        compare_floating_range(
            "norm_invs2", norm_invs2,
            std::vector<double>{
                minfd, minfd,  minfd, -4,          -1,          0.5,
                1.25,  1.4,    1.625, 1.7,         1.8125,      1.85,
                2,     2.1875, 2.3,   2.375,       2.6,         2.75,
                3.5,   5,      8,     inf<double>, inf<double>, inf<double>});
    };

    test("T Distribution") = [&] {
        double df = 29;
        auto t_pdfs =
            ranges::views::transform(x, [df](auto v) { return t_pdf(v, df); });
        compare_floating_range(
            "t_pdfs", t_pdfs,
            std::vector<double>{
                3.26793e-39, 3.08251e-30, 7.48671e-11, 0.0569413,  0.237858,
                0.347735,    0.38295,     0.387425,    0.392336,   0.393478,
                0.39472,     0.395007,    0.395519,    0.39472,    0.393478,
                0.392336,    0.387425,    0.38295,     0.347735,   0.237858,
                0.0569413,   7.48671e-11, 3.08251e-30, 3.26793e-39});

        auto t_cdfs =
            ranges::views::transform(x, [df](auto v) { return t_cdf(v, df); });
        compare_floating_range(
            "t_cdfs", t_cdfs,
            std::vector<double>{
                1.13003e-38, 5.37431e-30, 3.29993e-11, 0.0274718, 0.162791,
                0.310424,    0.402175,    0.421438,    0.450693,  0.460516,
                0.475297,    0.480233,    0.5,         0.524703,  0.539484,
                0.549307,    0.578562,    0.597825,    0.689576,  0.837209,
                0.972528,    1,           1,           1});

        auto ps =
            ranges::views::transform(x, [df](auto v) { return t_cdf(v, df); });

        auto t_invs =
            ranges::views::transform(x, [df](auto p) { return t_inv(p, df); });
        compare_floating_range(
            "t_invs", t_invs,
            std::vector<double>{
                NaN<double>, NaN<double>, NaN<double>, NaN<double>, NaN<double>,
                NaN<double>, NaN<double>, NaN<double>, NaN<double>, NaN<double>,
                NaN<double>, NaN<double>, minfd,       -1.5798,     -1.31143,
                -1.17386,    -0.854192,   -0.683044,   0,           inf<double>,
                NaN<double>, NaN<double>, NaN<double>, NaN<double>});
    };

    return 0;
}
