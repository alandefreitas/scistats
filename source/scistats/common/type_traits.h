//
// Created by Alan Freitas on 02/09/20.
//

#ifndef SCISTATS_TYPE_TRAITS_H
#define SCISTATS_TYPE_TRAITS_H

#include <type_traits>

#include <scistats/common/execution.h>

namespace scistats {

    template <typename C> struct is_iterable {
        typedef long false_type;
        typedef char true_type;

        template <class T> static false_type check(...);
        template <class T>
        static true_type check(int, typename T::const_iterator = C().end());

        enum { value = sizeof(check<C>(0)) == sizeof(true_type) };
    };

    template <typename C> constexpr bool is_iterable_v = is_iterable<C>::value;

    template <typename C> struct has_value_type {
        typedef long false_type;
        typedef char true_type;

        template <class T> static false_type check(...);
        template <class T>
        static true_type check(int, typename T::value_type = *C().begin());

        enum { value = sizeof(check<C>(0)) == sizeof(true_type) };
    };

    template <typename C>
    constexpr bool has_value_type_v = has_value_type<C>::value;

    template <typename C> struct has_iterable_value_type {
        typedef long false_type;
        typedef char true_type;

        template <class T> static false_type check(...);
        template <class T>
        static true_type
        check(int,
              typename T::value_type::value_type = *(C().begin()->begin()));

        enum { value = sizeof(check<C>(0)) == sizeof(true_type) };
    };

    template <typename C>
    constexpr bool has_iterable_value_type_v =
        has_iterable_value_type<C>::value;

    // Something like std::vector<double>
    template <class C>
    struct is_iterable_value
        : public std::integral_constant<
              bool, is_iterable_v<C> && !has_iterable_value_type_v<C>> {};

    template <typename C>
    constexpr bool is_iterable_value_v = is_iterable_value<C>::value;

    // Something like std::vector<std::vector<double>>
    template <class C>
    struct is_iterable_iterable
        : public std::integral_constant<
              bool, is_iterable_v<C> && has_iterable_value_type_v<C>> {};

    template <typename C>
    constexpr bool is_iterable_iterable_v = is_iterable_iterable<C>::value;

} // namespace scistats

#endif // SCISTATS_TYPE_TRAITS_H
