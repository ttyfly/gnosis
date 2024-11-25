#pragma once

#include <cmath>

#include "gnosis/utils.hpp"
#include "gnosis/fix.hpp"

namespace gnosis {
    constexpr float abs(const float s) {
        return s >= 0.f ? s : -s;
    }

    template<typename BaseType, std::size_t FracBits>
    constexpr Fix<BaseType, FracBits> abs(const Fix<BaseType, FracBits>& s) {
        Fix<BaseType, FracBits> res;
        res.data = s.data >= 0 ? s.data : -s.data;
        return res;
    }

    constexpr bool equal(const float a, const float b, const float eps = 1e-5f) {
        return abs(a - b) < eps;
    }

    template<typename BaseType, std::size_t FracBits>
    constexpr bool equal(const Fix<BaseType, FracBits>& a, const Fix<BaseType, FracBits>& b,
                         const Fix<BaseType, FracBits>& eps = Fix<BaseType, FracBits>(1e-5f)) {
        return a < b + eps && a > b - eps;
    }

    template<typename T>
    T sqrt(In<T> s) {
        return {};
    }

    template<>
    inline float sqrt(const float s) {
        return std::sqrt(s);
    }

    template<typename BaseType, std::size_t FracBits>
    Fix<BaseType, FracBits> sqrt(const Fix<BaseType, FracBits>& s) {
        if (s <= 0) {
            return 0;
        }

        Fix<BaseType, FracBits> r;

        // https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_(base_2)
        if constexpr (sizeof(BaseType) <= 4) {
            int64_t x = static_cast<int64_t>(s.data) << FracBits;
            int64_t c = 0;
            int64_t d = 1 << (sizeof(BaseType) * 8 - 2);
            while (d > x) {
                d >>= 2;
            }
            while (d != 0) {
                if (x >= c + d) {
                    x -= c + d;
                    c = (c >> 1) + d;
                }
                else {
                    c >>= 1;
                }
                d >>= 2;
            }
            r.data = c;
        }
        else {
            uint64_t x_hi = s.data >> 64 - FracBits;
            uint64_t x_lo = s.data << FracBits;
            uint64_t c_hi = 0;
            uint64_t c_lo = 0;
            uint64_t d_hi = 1 << 62 - (FracBits & -2ll);
            uint64_t d_lo = 0;
            while (d_hi > x_hi || (d_hi == x_hi && d_lo > x_lo)) {
                d_lo = d_hi << 62 | d_lo >> 2;
                d_hi >>= 2;
            }
            while (d_hi != 0 || d_lo != 0) {
                uint64_t c_d_lo;
                uint8_t carry = _addcarry_u64(0, c_lo, d_lo, &c_d_lo);
                uint64_t c_d_hi = c_hi + d_hi + carry;
                if (x_hi > c_d_hi || (x_hi == c_d_hi && x_lo >= c_d_lo)) {
                    uint8_t borrow = _subborrow_u64(0, x_lo, c_d_lo, &x_lo);
                    x_hi -= c_d_hi + borrow;
                    c_lo = c_hi << 63 | c_lo >> 1;
                    c_hi >>= 1;
                    carry = _addcarry_u64(0, c_lo, d_lo, &c_lo);
                    c_hi += d_hi + carry;
                }
                else {
                    c_lo = c_hi << 63 | c_lo >> 1;
                    c_hi >>= 1;
                }
                d_lo = d_hi << 62 | d_lo >> 2;
                d_hi >>= 2;
            }
            r.data = c_lo;
        }

        return r;
    }

    template<typename T>
    T cos(In<T> s) {
        return {};
    }

    template<typename T>
    T sin(In<T> s) {
        return {};
    }

    template<typename T>
    T tan(In<T> s) {
        return {};
    }

    template<typename T>
    T acos(In<T> s) {
        return {};
    }

    template<typename T>
    T asin(In<T> s) {
        return {};
    }

    template<typename T>
    T atan(In<T> s) {
        return {};
    }

    template<typename T>
    T atan2(In<T> c, In<T> s) {
        return {};
    }
}