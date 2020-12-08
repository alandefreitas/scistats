//
// Created by Alan Freitas on 02/09/20.
//

#ifndef SCISTATS_TYPE_TRAITS_H
#define SCISTATS_TYPE_TRAITS_H

// C++
#include <iterator>

// External

// Internal
#include <scistats/common/concepts.h>
#include <scistats/common/execution.h>

namespace scistats {
    template <typename T>
    struct iterator_or_range_traits {};

    template <Iterator T>
    struct iterator_or_range_traits<T> {
        using type = typename std::iterator_traits<T>::value_type;
    };

    template <Range T>
    struct iterator_or_range_traits<T> {
        using type = typename T::value_type;
    };

    template <typename T>
    using value_type = typename iterator_or_range_traits<T>::type;

    template <typename T>
    using pointer_type = typename std::iterator_traits<T>::pointer_type;

    template <class INTEGER>
    using promote_signed_integral = std::conditional_t<
        sizeof(INTEGER) <= 4, float,
        std::conditional_t<sizeof(INTEGER) <= 8, double, long double>>;

    template <class INTEGER>
    using promote_unsigned_interal =
        std::conditional_t<sizeof(INTEGER) <= 4, double, long double>;

    template <class INTEGER>
    using promote_integral =
        std::conditional_t<std::is_signed_v<INTEGER>,
                           promote_signed_integral<INTEGER>,
                           promote_unsigned_interal<INTEGER>>;

    template <class NUMBER_TYPE>
    using promote =
        std::conditional_t<std::is_integral_v<NUMBER_TYPE>,
                           promote_integral<NUMBER_TYPE>, NUMBER_TYPE>;

    template <class NUMBER_TYPE1, class NUMBER_TYPE2>
    using largest_type =
        std::conditional_t<sizeof(NUMBER_TYPE1) < sizeof(NUMBER_TYPE2),
                           NUMBER_TYPE2, NUMBER_TYPE1>;

} // namespace scistats

#endif // SCISTATS_TYPE_TRAITS_H
