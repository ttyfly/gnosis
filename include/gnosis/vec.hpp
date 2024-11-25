#pragma once

#define GNOSIS_FORCEINLINE __forceinline

namespace gnosis
{
    template<typename ScalarType, size_t ComponentNum>
    struct TVec
    {
        TVec<ScalarType, ComponentNum - 1> head;
        ScalarType last;
    };

    template<typename ScalarType>
    struct TVec<ScalarType, 0>
    {
    };

    template<size_t ComponentIndex, typename ScalarType, size_t ComponentNum>
    GNOSIS_FORCEINLINE ScalarType get(const TVec<ScalarType, ComponentNum> a)
    {
        static_assert(ComponentIndex < ComponentNum);
        if constexpr (ComponentIndex == ComponentNum - 1)
        {
            return a.last;
        }
        else
        {
            return get<ComponentIndex>(a.head);
        }
    }

    template<typename ScalarType, size_t ComponentNum>
    GNOSIS_FORCEINLINE TVec<ScalarType, ComponentNum + 1> append(TVec<ScalarType, ComponentNum> v,
                                                                 ScalarType s)
    {
        TVec<ScalarType, ComponentNum + 1> r;
        r.head = v;
        r.last = s;
        return r;
    }

    template<typename T>
    GNOSIS_FORCEINLINE T add(T a, T b)
    {
        return a + b;
    }

    template<typename ScalarType, size_t ComponentNum>
    GNOSIS_FORCEINLINE TVec<ScalarType, ComponentNum> add(const TVec<ScalarType, ComponentNum> a,
                                                          const TVec<ScalarType, ComponentNum> b)
    {
        return append(add(a.head, b.head), add(a.last, b.last));
    }

    template<typename T>
    GNOSIS_FORCEINLINE T sub(T a, T b)
    {
        return a - b;
    }
}