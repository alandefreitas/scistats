//
// Created by Alan Freitas on 18/11/20.
//

#ifndef SCISTATS_CONCEPTS_H
#define SCISTATS_CONCEPTS_H

// C++
#include <concepts>

// External
#include <range/v3/iterator/concepts.hpp>
#include <range/v3/range/concepts.hpp>

// Internal
#include <scistats/common/execution.h>

namespace scistats {
    template <typename T>
    concept Range = ranges::cpp20::range<T>;

    template <typename T>
    concept Iterator = ranges::cpp20::input_iterator<T>;

    template <typename T>
    struct is_const_pointer {
        static const bool value = false;
    };

    template <typename T>
    struct is_const_pointer<const T *> {
        static const bool value = true;
    };

    template <typename TIterator>
    struct is_const_iterator {
        typedef typename std::iterator_traits<TIterator>::pointer pointer;
        static const bool value = is_const_pointer<pointer>::value;
    };

    template <class T>
    constexpr bool is_const_iterator_v = is_const_iterator<T>::value;

    template <typename T>
    concept ConstIterator = Iterator<T> &&is_const_iterator_v<T>;

    template <typename T>
    concept ExecutionPolicy = is_execution_policy_v<T>;

    template <typename T>
    concept Number = std::is_arithmetic_v<T>;

    template <typename T>
    concept Floating = std::is_floating_point_v<T>;

    template <typename T>
    concept Integer = std::is_integral_v<T>;

    template <typename T>
    concept FloatingOrInteger = Floating<T> || Integer<T>;

    template <class F, class... Args>
    concept Callable = std::is_invocable_v<F, Args...>;

} // namespace scistats

#endif // SCISTATS_CONCEPTS_H
