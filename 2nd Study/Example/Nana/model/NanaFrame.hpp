#ifndef _NANA_FRAME_HPP_
#define _NANA_FRAME_HPP_

#include <nana/gui.hpp>

#include "./IFrame.h"
#include "./NanaPanel.h"

namespace sample
{

    template <typename Panel>
    class NanaFrame : 
        public IFrame
    {
    protected:
        nana::form fm;
        uptr<NanaPanel> root_panel = nullptr;

    public:
        explicit NanaFrame()
        {
            root_panel = make_panel<Panel>(fm.handle());

            // Adjust current panel size
            root_panel->resize(fm.size().width,
                               fm.size().height);

            // Attach resize event handler
            fm.events().resized([&](const nana::arg_resized& _e)
            {
                // forward resize event to children
                this->root_panel->resize(_e.width, _e.height);
            });

            // Visualize
            root_panel->show();
        }

        // self resize
        void    resize(const u32 _w,
                       const u32 _h) override
        {
            // trigger resize event
            fm.size(size{ _w, _h });
        }

        void    show() override 
        {
            this->fm.show();
        }

        void    hide() override 
        {
            this->fm.hide();
        }

        IPanel& root() override
        {
            return *(this->root_panel);
        }

    };
}

#endif
