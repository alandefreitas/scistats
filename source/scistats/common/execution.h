//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_EXECUTION_H
#define SCISTATS_EXECUTION_H

#include <type_traits>

namespace scistats::execution {
    /// Sequenced execution policy:
    /// Sequenced algorithm's execution may not be parallelized
    class sequenced_policy {};

    /// Parallel execution policy:
    /// Parallel algorithm's execution may be parallelized
    class parallel_policy {};

    /// Execution policy objects
    inline constexpr sequenced_policy seq{/*unspecified*/};
    inline constexpr parallel_policy par{/*unspecified*/};

} // namespace scistats::execution

namespace scistats {
    // Execution policy type trait
    template <class T>
    using is_execution_policy =
        std::conditional_t<std::is_same_v<T, execution::sequenced_policy> ||
                               std::is_same_v<T, execution::parallel_policy>,
                           std::true_type, std::false_type>;

    // Execution policy type trait value
    template <class T>
    constexpr bool is_execution_policy_v = is_execution_policy<T>::value;

} // namespace scistats

#endif // SCISTATS_EXECUTION_H
