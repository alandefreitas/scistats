#include <boost/ut.hpp>
#include <random>
#include <scistats/bayesian/bootstrap.h>
#include <scistats/bayesian/theorem.h>
#include <scistats/descriptive/mean.h>
#include <vector>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    test("Bayes Theorem") = [&] {
        // Bayes theorem
        double p_hypothesis = 0.2;
        double likelihood = 0.8;
        double p_evidence = 0.6;
        expect(bayes_theorem(likelihood, p_hypothesis, p_evidence) == 0.26_d);
    };

    test("Bootstrap") = [&] {
        int i = 0;
        auto generate_i_values = [&]() { return i++; };

        auto v = bootstrap(generate_i_values, 1000);
        expect(sum(v) == 499500_i);
    };

    return 0;
}
