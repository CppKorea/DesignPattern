#pragma once

#include "./timer.hpp"
#include <iostream>

namespace Pattern
{
    using u8 = std::uint8_t;
    using i32 = std::int32_t;

    struct Pos2D
    {
        i32 x{ 0 }, y{ 0 };
    public:
        Pos2D() {};
        Pos2D(i32 _x, i32 _y) :
            x{ _x }, y{ _y }
        {}
    };

    
    template <typename UnitType>
    struct Updatable
    {
        virtual void update(UnitType _time) = 0;
    };

    using updatable = Updatable<std::chrono::milliseconds>;

}// namespace Pattern
