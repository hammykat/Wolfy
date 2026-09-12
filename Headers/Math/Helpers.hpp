//
// Created by berke on 9/13/2026.
//

#ifndef WOLFY_HELPERS_HPP
#define WOLFY_HELPERS_HPP

namespace MathHelpers {
    template <typename T, typename U, typename V>
    float Lerp(T a, U b, V t) {
        using CommonType = std::common_type_t<T, U, V>;
        auto a_c = static_cast<CommonType>(a);
        auto b_c = static_cast<CommonType>(b);
        auto t_c = static_cast<CommonType>(t);

        return a_c + (b_c - a_c) * t_c;
    }

    template <typename T, typename U, typename V>
    float InverseLerp(T a, U b, V v) {
        using CommonType = std::common_type_t<T, U, V>;

        auto a_c = static_cast<CommonType>(a);
        auto b_c = static_cast<CommonType>(b);
        auto v_c = static_cast<CommonType>(v);

        if (a_c == b_c) return static_cast<CommonType>(0);

        // Cast to float to avoid integer divison
        return static_cast<float>(v_c - a_c) / static_cast<float>(b_c - a_c);
    }
}

#endif //WOLFY_HELPERS_HPP