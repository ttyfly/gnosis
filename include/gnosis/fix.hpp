#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

#if defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(_mul128)
#pragma intrinsic(_div128)
#endif

#include "gnosis/utils.hpp"

namespace gnosis {
    template<typename _BaseType, std::size_t _FracBits>
    struct Fix {
        static_assert(sizeof(_BaseType) * 8 > _FracBits);

        using BaseType = _BaseType;
        constexpr static std::size_t FRAC_BITS = _FracBits;

        BaseType data;

        constexpr Fix() : data(0) {}
        constexpr Fix(const Fix& other) = default;
        constexpr Fix(const int integer_value) {
            data = static_cast<BaseType>(integer_value) << FRAC_BITS;
        }
        constexpr explicit Fix(const float float_value) {
            const int32_t float_data = std::bit_cast<int32_t>(float_value);
            if (float_data == 0) {
                data = 0;
                return;
            }

            int32_t value = 0x80'0000 | (float_data & 0x7f'ffff);
            if (float_data < 0) {
                value = ~value + 1;
            }

            const int32_t offset = ((float_data & 0x7f80'0000) >> 23) - 127 + FRAC_BITS - 23;
            if (-offset > 24) {
                data = 0;
            }
            else if (offset >= static_cast<int32_t>(sizeof(BaseType) * 8ull) - 24) {
                data = static_cast<BaseType>(1) << (sizeof(BaseType) * 8 - 1);
            }
            else if (offset > 0) {
                data = static_cast<BaseType>(value) << offset;
            }
            else if (offset < 0) {
                data = static_cast<BaseType>(value) >> -offset;
            }
            else {
                data = static_cast<BaseType>(value);
            }
        }

        constexpr explicit operator double() const {
            return static_cast<double>(data) / (1ll << FRAC_BITS);
        }
        constexpr explicit operator float() const {
            return static_cast<float>(static_cast<double>(*this));
        }
        constexpr explicit operator int() const {
            return data >> FRAC_BITS;
        }

        constexpr void operator+=(const Fix& other) {
            data += other.data;
        }
        constexpr void operator-=(const Fix& other) {
            data -= other.data;
        }
        constexpr void operator*=(const Fix& other) {
            if constexpr (sizeof(BaseType) <= 4) {
                data = (static_cast<int64_t>(data) * other.data) >> FRAC_BITS;
            }
            else {
#if defined(_MSC_VER)
                int64_t hi;
                const uint64_t lo = _mul128(data, other.data, &hi);
                data = (hi << (64 - FRAC_BITS)) + (lo >> FRAC_BITS);
#else
                data = (static_cast<__int128>(data) * other.data) >> FRAC_BITS;
#endif
            }
        }
        constexpr void operator/=(const Fix& other) {
            if constexpr (sizeof(BaseType) <= 4) {
                data = (static_cast<int64_t>(data) << FRAC_BITS) / other.data;
            }
            else {
#if defined(_MSC_VER)
                const int64_t hi = data >> (64 - FRAC_BITS);
                const int64_t lo = data << FRAC_BITS;
                int64_t remainder;
                data = _div128(hi, lo, other.data, &remainder);
#else
                result.data = (static_cast<__int128>(data) << FRAC_BITS) / other.data;
#endif
            }
        }
        constexpr Fix operator+(const Fix& other) const {
            Fix result = *this;
            result += other;
            return result;
        }
        constexpr Fix operator-(const Fix& other) const {
            Fix result = *this;
            result -= other;
            return result;
        }
        constexpr Fix operator*(const Fix& other) const {
            Fix result = *this;
            result *= other;
            return result;
        }
        constexpr Fix operator/(const Fix& other) const {
            Fix result = *this;
            result /= other;
            return result;
        }
    };

    template<typename BaseType, std::size_t FracBits>
    bool operator<(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b) {
        return a.data < b.data;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator>(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b) {
        return a.data > b.data;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator<=(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b) {
        return a.data <= b.data;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator>=(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b) {
        return a.data >= b.data;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator==(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b) {
        return a.data == b.data;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator<(const Fix<BaseType, FracBits>& a, const int b) {
        return a.data < static_cast<int64_t>(b) << FracBits;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator>(const Fix<BaseType, FracBits>& a, const int b) {
        return a.data > static_cast<int64_t>(b) << FracBits;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator<=(const Fix<BaseType, FracBits>& a, const int b) {
        return a.data <= static_cast<int64_t>(b) << FracBits;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator>=(const Fix<BaseType, FracBits>& a, const int b) {
        return a.data >= static_cast<int64_t>(b) << FracBits;
    }
    template<typename BaseType, std::size_t FracBits>
    bool operator==(const Fix<BaseType, FracBits>& a, const int b) {
        return a.data == static_cast<int64_t>(b) << FracBits;
    }

    template<typename BaseType, std::size_t FracBits>
    std::ostream& operator<<(std::ostream& os, const Fix<BaseType, FracBits>& obj) {
        os << std::to_string(static_cast<float>(obj));
        return os;
    }
    template<typename BaseType, std::size_t FracBits>
    struct InParam<Fix<BaseType, FracBits>> { using Type = const Fix<BaseType, FracBits>&; };
}