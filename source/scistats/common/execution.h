//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_EXECUTION_H
#define SCISTATS_EXECUTION_H

namespace scistats::execution {
    // sequenced execution policy: parallel algorithm's execution may not be
    // parallelized
    class sequenced_policy {};

    // parallel execution policy: parallel algorithm's execution may be
    // parallelized
    class parallel_policy {};

    // execution policy objects
    inline constexpr sequenced_policy seq{/*unspecified*/};
    inline constexpr parallel_policy par{/*unspecified*/};
} // namespace scistats::execution

namespace scistats {
    // execution policy type trait
    template <class T> struct is_execution_policy { bool value = false; };

    template <class T>
    inline constexpr bool is_execution_policy_v = is_execution_policy<T>::value;

    // execution policy type trait
    template <> struct is_execution_policy<execution::sequenced_policy> {
        bool value = true;
    };

    template <> struct is_execution_policy<execution::parallel_policy> {
        bool value = true;
    };

} // namespace scistats

#endif // SCISTATS_EXECUTION_H
