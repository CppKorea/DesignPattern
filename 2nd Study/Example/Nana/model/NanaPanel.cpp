#include "./NanaPanel.h"

namespace sample
{
    // Nana Single Panel
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    nana::window NanaPanel::parent() const
    {
        return pnl.parent();
    }

    nana::window NanaPanel::handle() const {
        return this->pnl.handle();
    }

    u32 NanaPanel::width() const
    {
        return this->pnl.size().width;
    }

    void NanaPanel::width(const u32 _w)
    {
        resize(_w, height());
    }

    u32 NanaPanel::height() const
    {
        return this->pnl.size().height;
    }
    
    void NanaPanel::height(const u32 _h)
    {
        resize(width(), _h);
    }
    
    void NanaPanel::resize(const u32 _w, const u32 _h)
    {
        this->pnl.size(nana::size{ _w, _h });
    }

    void NanaPanel::move_to(const i32 _off_x, const i32 _off_y)
    {
        this->pnl.move(_off_x, _off_y);
    }
    
    void NanaPanel::background(const u32 _rgba)
    {
        nana::color c = static_cast<nana::color_rgba>(_rgba);
        this->background(c);
    }

    void NanaPanel::background(const nana::color _color)
    {
        this->pnl.bgcolor(_color);
    }

    // In single panel, do nothing
    void NanaPanel::append(uptr<IPanel>&& _pnl)
    {
        return;
    }

    void NanaPanel::show() {
        this->pnl.show();
    }

    void NanaPanel::hide() {
        this->pnl.hide();
    }



    // Nana Vertical Panel
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    void NanaVPanel::resize(const u32 _w, const u32 _h)
    {
        this->pnl.size(nana::size{ _w,_h });

        // X-axis coordinate offset 
        // Since this is **vertical** panel, 
        // no change for `offset_x`
        const u32 offset_x = 0;
        // Y-axis coordinate offset 
        u32 offset_y = 0;

        const size_t N = this->ls_child.size();
        // Avoid divide by 0 exception!
        if (N == 0) { return; }

        const u32 W = _w;
        const u32 H = _h / N;

        auto iter = ls_child.begin();
        while (iter != ls_child.end()) 
        {
            // child panel
            auto& cp = *iter;
            
            cp->resize(W, H);
            cp->move_to(offset_x, offset_y);

            // increase y offset
            offset_y += H;

            // go to next!
            iter++;
        }
    }

    //void NanaVPanel::background(const u32 _rgba)
    //{
    //    nana::color c = static_cast<nana::color_rgba>(_rgba);
    //    this->background(c);
    //}

    //void NanaVPanel::background(const nana::color _color)
    //{
    //    this->pnl.bgcolor(_color);
    //}

    void NanaVPanel::append(uptr<IPanel>&& _pnl)
    {
        this->ls_child.emplace_back(std::move(_pnl));
    }

    // Nana Horizontal Panel
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    void NanaHPanel::resize(const u32 _w, const u32 _h)
    {
        this->pnl.size(nana::size{ _w,_h });

        // X-axis coordinate offset 
        u32 offset_x = 0;
        // Y-axis coordinate offset 
        // Since this is **Horizontal** panel, 
        // no change for `offset_x`
        const u32 offset_y = 0;

        const size_t N = this->ls_child.size();
        // Avoid divide by 0 exception!
        if (N == 0) {   return; }

        const u32 W = _w / N;
        const u32 H = _h;

        auto iter = ls_child.begin();
        while (iter != ls_child.end())
        {
            // child panel
            auto& cp = *iter;

            cp->resize(W, H);
            cp->move_to(offset_x, offset_y);

            // increase y offset
           offset_x += W;

           // go to next!
           iter++;
        }
    }

    void NanaHPanel::append(uptr<IPanel>&& _pnl)
    {
        this->ls_child.emplace_back(std::move(_pnl));
    }

}

