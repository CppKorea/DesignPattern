#ifndef _NANA_PANEL_H_
#define _NANA_PANEL_H_

#include <list>
#include <algorithm>

#include <nana/gui.hpp>
#include <nana/gui/widgets/panel.hpp>

#include "./IPanel.hpp"

namespace sample
{

    // Nana single panel
    // Basic panel implementation for [nana] gui library
    class NanaPanel :
        public IPanel
    {
    protected:
        // nana panel (with background)
        nana::panel<true> pnl;

    public:
        // - Note
        //      nana window handle
        nana::window parent() const;

        // - Note
        //      nana window handle
        nana::window handle() const;


        explicit NanaPanel(nana::window _parent):
            pnl{_parent}
        {}

        void    background(const nana::color _color);

    public:
        // Interface implementation

        u32     width()     const override;
        void    width(const u32 _w) override;

        u32     height()     const override;
        void    height(const u32 _h) override;

        void    resize(const u32 _w,
                       const u32 _h) override;

        void    move_to(const i32 _off_x,
                        const i32 _off_y) override;

        void    background(const u32 _rgba) override;

        // In single panel, do nothing.
        void    append(uptr<IPanel>&& _pnl) override;

        void    show() override;
        void    hide() override;

    };


    // Nana Vertical Panel
    class NanaVPanel : 
        public NanaPanel
    {
        using elem_type = uptr<IPanel>;

        std::list<elem_type> ls_child;

    public:
        explicit NanaVPanel(nana::window _parent) :
            NanaPanel{ _parent }
        {}

        void    resize(const u32 _w,
                       const u32 _h) override;

        // Append children panel
        void    append(uptr<IPanel>&& _pnl) override;

    };

    // Nana Horizontal Panel
    class NanaHPanel :
        public NanaPanel
    {
        using elem_type = uptr<IPanel>;

        std::list<elem_type> ls_child;

    public:
        explicit NanaHPanel(nana::window _parent) :
            NanaPanel{ _parent }
        {}

        void    resize(const u32 _w,
                       const u32 _h) override;
        // add children panel
        void    append(uptr<IPanel>&& _pnl) override;
    };

}// namespace sample

#endif 
