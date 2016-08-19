#ifndef _INTERFACE_PANEL_HPP_
#define _INTERFACE_PANEL_HPP_

#include <memory>
#include <cstdint>
#include <list>

namespace sample
{
    template <typename T>
    using uptr = std::unique_ptr<T>;

    using u32 = std::uint32_t;
    using i32 = std::int32_t;

    // panel interface
    struct IPanel
    {
        virtual u32     width()     const = 0;
        virtual void    width(const u32 _w) = 0;

        virtual u32     height()     const = 0;
        virtual void    height(const u32 _h) = 0;

        virtual void    resize(const u32 _w, 
                               const u32 _h) = 0;

        virtual void    move_to(const i32 _off_x,
                                const i32 _off_y) = 0;

        virtual void    background(const u32 _rgba) = 0;

        virtual void    append(uptr<IPanel>&& _pnl) = 0;

        virtual void    show() = 0;
        virtual void    hide() = 0;

    };

    // Boxing function for Panel
    template <typename Panel, typename... Args>
    uptr<Panel> make_panel(Args&&... params)
    {
        return std::make_unique<Panel>(std::move(params...));
    }


} // namespace sample

#endif
