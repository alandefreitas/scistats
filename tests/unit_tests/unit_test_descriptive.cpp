#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <scistats/descriptive/bounds.h>
#include <scistats/descriptive/cov.h>
#include <scistats/descriptive/max.h>
#include <scistats/descriptive/mean.h>
#include <scistats/descriptive/median.h>
#include <scistats/descriptive/min.h>
#include <scistats/descriptive/mode.h>
#include <scistats/descriptive/stddev.h>
#include <scistats/descriptive/var.h>
#include <vector>

TEST_CASE("Mean") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(mean(x.begin(), x.end()) == Approx(1.91667));
    REQUIRE(mean(x) == Approx(1.91667));
    REQUIRE(mean(execution::seq, x) == Approx(1.91667));
    REQUIRE(mean(execution::par, x) == Approx(1.91667));
}

TEST_CASE("Median") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(median(x) == 2);
}

TEST_CASE("Mode") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(mode(x) == 2);
}

TEST_CASE("Min") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(min(x) == 0);
    REQUIRE(min(execution::par, x) == 0);

    REQUIRE(scistats::min(1, 2) == 1);
    REQUIRE(scistats::min(1, 2, 3) == 1);
    REQUIRE(min(1, 2, 3, 6) == 1);
    REQUIRE(min(2, 3, 1, 6) == 1);
}

TEST_CASE("Max") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(max(x) == 4);
    REQUIRE(max(execution::par, x) == 4);

    REQUIRE(scistats::max(1, 2) == 2);
    REQUIRE(scistats::max(1, 2, 3) == 3);
    REQUIRE(max(1, 2, 3, 6) == 6);
    REQUIRE(max(2, 6, 1, 3) == 6);
}

TEST_CASE("Bounds") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    auto b = bounds(x);
    REQUIRE(b.first == 0);
    REQUIRE(b.second == 4);
    b = bounds(execution::par, x);
    REQUIRE(b.first == 0);
    REQUIRE(b.second == 4);
}

TEST_CASE("Variance") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(var(x) == Approx(1.17424));
    REQUIRE(var(execution::par, x) == Approx(1.17424));
}

TEST_CASE("Standard deviation") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(stddev(x) == Approx(1.08362));
    REQUIRE(stddev(execution::par, x) == Approx(1.08362));
}

TEST_CASE("Covariance") {
    using namespace scistats;
    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    REQUIRE(cov(x, x) == Approx(1.17424));
    REQUIRE(cov(execution::par, x, x) == Approx(1.17424));

    std::vector<int> x10 = {0, 10, 10, 20, 30, 20, 10, 30, 20, 40, 20, 20};
    REQUIRE(cov(x, x10) == Approx(11.7424));
    REQUIRE(cov(execution::par, x, x10) == Approx(11.7424));
}