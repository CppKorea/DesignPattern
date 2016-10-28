#pragma once
#include "./buffer.h"

namespace Pattern
{
    using u8 = std::uint8_t;

    struct Pos2D
    {
        i32 x = 0, y = 0;
    public:
        Pos2D(i32 _x, i32 _y) :
            x{ _x }, y{ _y }
        {}
    };
    
    // - Note
    //      CSS-like 4 byte color type with RGB-A notation
    //      In this type, Alpha's value domain is 0 ~ 255.
    //
    //      a == 255 : CSS alpha 1.0 (default)
    //      a ==   0 : CSS alpha 0.0
    //
    struct PixelColor final
    {
        union {
            struct {
                u8 red;
                u8 green;
                u8 blue;
                u8 alpha;
            };
            u32 rgba;
        };

        PixelColor(const u32 _rgba = 0xff) :
            rgba{ _rgba }
        {}

        PixelColor( const u8 _red, 
                    const u8 _green, 
                    const u8 _blue, 
                    const u8 _alpha = 0xff ) :
            red{ _red }, green{_green}, blue{_blue}, alpha{_alpha}
        {}

        operator u32() const noexcept
        {
            return this->rgba;
        }
    };


    // - Dependency
    //      `PixelColor`
    template <u32 Width, u32 Height>
    class FrameBuffer :
            public StaticBuffer<PixelColor, Width * Height>
    {
        using base_type = StaticBuffer<PixelColor, Width * Height>;
    public:
        using value_type = PixelColor;

    public:
        value_type& operator[](const Pos2D _pos) noexcept(false)
        {
            return base_type::operator[](_pos.x  + _pos.y * Width);
        }

        const value_type& operator[](const Pos2D _pos) const noexcept(false)
        {
            return base_type::operator[](_pos.x + _pos.y * Width);
        }


    };


}