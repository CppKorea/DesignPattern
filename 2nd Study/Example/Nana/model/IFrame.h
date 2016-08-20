#ifndef _INTERFACE_FRAME_H_
#define _INTERFACE_FRAME_H_

#include "./IPanel.hpp" 

namespace sample
{
    class IFrame
    {
    public:
        virtual
        void    resize(const u32 _w,
                       const u32 _h) = 0;

        virtual void    show() = 0;
        virtual void    hide() = 0;

        virtual IPanel& root() = 0;

    };
}

#endif 
