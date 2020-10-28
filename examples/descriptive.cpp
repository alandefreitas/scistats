#include <iostream>
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

int main() {
    using namespace scistats;
    using std::cout;
    using std::endl;

    std::vector<int> x = {0, 1, 1, 2, 3, 2, 1, 3, 2, 4, 2, 2};

    ///////////////////////////////////////////////////////
    /// Central tendency                                ///
    ///////////////////////////////////////////////////////
    cout << mean(x.begin(), x.end()) << endl;
    cout << mean(x) << endl;
    cout << mean(execution::seq, x) << endl;
    cout << mean(execution::par, x) << endl;

    cout << median(x) << endl;

    cout << mode(x) << endl;

    ///////////////////////////////////////////////////////
    /// Dispersion                                      ///
    ///////////////////////////////////////////////////////
    cout << min(x) << endl;
    cout << min(execution::par, x) << endl;

    cout << min(1, 2) << endl;
    cout << min(1, 2, 3) << endl;
    cout << min(1, 2, 3, 6) << endl;

    cout << max(x) << endl;
    cout << max(execution::par, x) << endl;

    cout << max(1, 2) << endl;
    cout << max(1, 2, 3) << endl;
    cout << max(1, 2, 3, 6) << endl;

    auto b = bounds(x);
    cout << b.first << " " << b.second << endl;
    b = bounds(execution::par, x);
    cout << b.first << " " << b.second << endl;

    cout << var(x) << endl;
    cout << var(execution::par, x) << endl;

    cout << stddev(x) << endl;
    cout << stddev(execution::par, x) << endl;

    ///////////////////////////////////////////////////////
    /// Correlation                                     ///
    ///////////////////////////////////////////////////////
    cout << cov(x, x) << endl;
    cout << cov(execution::par, x, x) << endl;

    std::vector<int> x10 = {0, 10, 10, 20, 30, 20, 10, 30, 20, 40, 20, 20};
    cout << cov(x, x10) << endl;
    cout << cov(execution::par, x, x10) << endl;

    return 0;
}
