#pragma once

namespace gnosis {
    template<typename T>
    struct InParam { using Type = const T&; };

    template<>
    struct InParam<double> { using Type = double; };

    template<>
    struct InParam<float> { using Type = float; };

    template<>
    struct InParam<int> { using Type = int; };

    template<typename T>
    using In = typename InParam<T>::Type;
}