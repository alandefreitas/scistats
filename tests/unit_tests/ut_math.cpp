#include <boost/ut.hpp>
#include <scistats/math/abs.h>
#include <scistats/math/acot.h>
#include <scistats/math/beta.h>
#include <scistats/math/beta_inc.h>
#include <scistats/math/beta_inc_inv.h>
#include <scistats/math/beta_inc_upper.h>
#include <scistats/math/betaln.h>
#include <scistats/math/constants.h>
#include <scistats/math/cot.h>
#include <scistats/math/erfinv.h>
#include <scistats/math/gammaln.h>
#include <scistats/math/is_even.h>
#include <scistats/math/is_odd.h>
#include <scistats/math/prod.h>
#include <scistats/math/sum.h>
#include <scistats/math/xinbta.h>

#include <vector>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    test("Constants") = [&] {
        expect(pi<float>() == 3.14_f);
        expect(pi<double>() == 3.14_d);
        expect(pi<long double>() == 3.14_ld);
        expect(pi<double>() == 3.14159_d);
        expect(epsilon<double>() == 0.00000_d);
        expect(std::isinf(inf<double>()));
        expect(almost_equal(min<double>(), std::numeric_limits<double>::min()));
        expect(almost_equal(max<double>(), std::numeric_limits<double>::max()));
        expect(std::isnan(NaN<double>()));
        expect(e<double>() == 2.71828_d);
        expect(euler<double>() == 0.577216_d);
        expect(log2_e<double>() == 1.4427_d);
        expect(log10_e<double>() == 0.434294_d);
        expect(sqrt2<double>() == 1.41421_d);
        expect(sqrt1_2<double>() == 0.707107_d);
        expect(sqrt3<double>() == 1.73205_d);
        expect(pi_2<double>() == 1.5708_d);
        expect(pi_4<double>() == 0.785398_d);
        expect(sqrt_pi<double>() == 1.77245_d);
        expect(two_sqrt_pi<double>() == 1.12838_d);
        expect(one_by_pi<double>() == 0.31831_d);
        expect(two_by_pi<double>() == 0.63662_d);
        expect(ln10<double>() == 2.30259_d);
        expect(ln2<double>() == 0.693147_d);
        expect(lnpi<double>() == 1.14473_d);
    };

    std::vector<int> x = {6, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};
    std::vector<int> x2 = {29, 46, 58, 42, 2,  43, 20, 84, 84, 74,
                           45, 88, 51, 67, 54, 30, 73, 69, 39, 13,
                           16, 88, 45, 24, 22, 64, 77, 87, 77, 84};

    test("Sum") = [&] {
        expect(sum(x) == 29_i);
        expect(sum(x.begin(), x.end()) == 29_i);
        expect(sum(execution::seq, x) == 29_i);
        expect(sum(execution::par, x) == 29_i);

        expect(sum(x2) == 1595_i);
        expect(sum(x2.begin(), x2.end()) == 1595_i);
        expect(sum(execution::seq, x2) == 1595_i);
        expect(sum(execution::par, x2) == 1595_i);
    };

    test("Prod") = [&] {
        expect(prod(x) == 6912_i);
        expect(prod(x.begin(), x.end()) == 6912_i);
        expect(prod(execution::seq, x) == 6912_i);
        expect(prod(execution::par, x) == 6912_i);
    };

    test("C++ constrained overloads") = [&] {
        expect(abs(2 - 6) == 4_i);
        expect(abs(2. - 6.) == 4._d);
    };

    test("Trigonometry") = [&] {
        expect(acot(0.) == 1.5708_d);
        expect(std::isinf(cot(0.)));
        expect(cot(1.) == 0.6420_d);
    };

    test("Test functions") = [&] {
        expect(almost_equal(1., 1.));
        expect(is_even(0));
        expect(is_odd(1));
        expect(is_even(2));
        expect(is_odd(3));
        expect(is_even(4));
    };

    test("Special Functions") = [&] {
        expect(std::isinf(betaln(0., 1.)));
        expect(std::isinf(beta(0., 1.)));
        expect(beta_inc(0., 1., 1.) == 0._d);
        expect(beta_inc_inv(0., 1., 1.) == 0._d);
        expect(beta_inc_upper(0., 1., 1.) == 1._d);
        expect(std::isnan(erfinv(42.)));
        expect(std::isinf(erfinv(1.)));
        expect(std::isinf(erfinv(-1.)));
        expect(erfinv(0.5) == 0.476936_d);
        expect(std::isnan(erfinv_simple(42.)));
        expect(std::isinf(erfinv_simple(1.)));
        expect(std::isinf(erfinv_simple(-1.)));
        expect(erfinv_simple(0.5) == 0.476996_d);
        expect(gammaln(42.) == 114.034_d);
        expect(xinbta(1., 1., 0.0, 0.0) == 0.0_d);
        expect(xinbta(1., 1., 0.0, 1.0) == 1.0_d);
    };

    return 0;
}
