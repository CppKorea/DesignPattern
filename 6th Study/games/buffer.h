#pragma once

#include <cstdint>
#include <type_traits>

namespace Pattern
{
    using i32 = std::int32_t;
    using u32 = std::uint32_t;

    template <typename T>
    struct basic_buffer
    {
    protected:
        basic_buffer() = default;
        ~basic_buffer() = default;
    public:
        virtual T&        operator [](const i32 _idx)       noexcept(false) = 0;
        virtual const T&  operator [](const i32 _idx) const noexcept(false) = 0;
        virtual void      clear() = 0;
    };


    template <typename T, u32 Size>
    class StaticBuffer : 
            public basic_buffer<T>
    {
        static_assert(std::is_default_constructible<T>::value, 
            "The buffer's element type must be [default constructible]");
        static_assert(std::is_copy_assignable<T>::value,
            "The buffer's element type must be [copy assignable]");

        T blocks[Size];

    public:
        StaticBuffer() = default;

        void clear() noexcept 
            override
        {
            for (auto i = 0; i < Size; ++i) {
                // Assign default value
                blocks[i] = T{};
            }
        }

        T& operator [](const i32 _idx) noexcept(false) 
            override
        {
            return blocks[_idx];
        }

        const T& operator [](const i32 _idx) const  noexcept(false)
            override
        {
            return blocks[_idx];
        }

    };


}// namespace Pattern

