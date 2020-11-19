#include <boost/ut.hpp>
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>
#include <scistats/common/type_traits.h>
#include <vector>

int main() {
    using namespace boost::ut;
    using namespace scistats;

    test("Execution Policy") = [&] {
        expect(std::is_same_v<std::decay_t<decltype(execution::seq)>,
                              execution::sequenced_policy>);
        expect(std::is_same_v<std::decay_t<decltype(execution::par)>,
                              execution::parallel_policy>);
        expect(is_execution_policy<execution::sequenced_policy>::value);
        expect(is_execution_policy<execution::parallel_policy>::value);
        expect(!is_execution_policy<double>::value);
        expect(is_execution_policy_v<execution::sequenced_policy>);
        expect(is_execution_policy_v<execution::parallel_policy>);
        expect(!is_execution_policy_v<double>);
    };

    test("Type traits") = [&] {
        expect(
            std::is_same_v<value_type<std::vector<double>::iterator>, double>);
        expect(std::is_same_v<promote<int>, float>);
        expect(std::is_same_v<promote<long>, double>);
        expect(std::is_same_v<promote<unsigned int>, double>);
        expect(std::is_same_v<promote<unsigned long>, long double>);
        expect(std::is_same_v<promote<float>, float>);
        expect(std::is_same_v<promote<double>, double>);
    };

    test("Concepts") = [&] {
        expect(Range<std::vector<double>>);
        expect(!Range<std::vector<double>::iterator>);
        expect(!Range<std::vector<double>::const_iterator>);
        expect(!Range<double>);

        expect(!Iterator<std::vector<double>>);
        expect(Iterator<std::vector<double>::iterator>);
        expect(Iterator<std::vector<double>::const_iterator>);
        expect(!Iterator<double>);

        expect(!ExecutionPolicy<std::vector<double>>);
        expect(!ExecutionPolicy<std::vector<double>::iterator>);
        expect(!ExecutionPolicy<std::vector<double>::const_iterator>);
        expect(!ExecutionPolicy<double>);
        expect(ExecutionPolicy<execution::sequenced_policy>);
        expect(ExecutionPolicy<execution::parallel_policy>);
    };

    return 0;
}
