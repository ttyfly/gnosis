#pragma once

#include <string>

#include "fix.hpp"

namespace gnosis {
    std::string to_string(const float scalar) {
        return std::to_string(scalar);
    }

    template<typename BaseType, std::size_t FracBits>
    std::string to_string(const Fix<BaseType, FracBits> scalar) {
        return std::to_string(static_cast<float>(scalar));
    }
}