//
// Created by Alan Freitas on 27/09/20.
//

#ifndef SCISTATS_PROMOTE_H
#define SCISTATS_PROMOTE_H

#include <type_traits>

namespace scistats {
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
} // namespace scistats

#endif // SCISTATS_PROMOTE_H
