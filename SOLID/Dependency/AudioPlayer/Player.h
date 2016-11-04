#pragma once

#include "./Sound.h"
namespace Pattern
{
    class Player 
    {
    public:

        void update();
        void pause();
        void resume();
        void stop();

        void play(Sound& _sound);
        void play(Sound& _sound, bool _option);


        template <typename SetOption>
        decltype(auto) set(SetOption option)
        {
            return option.set(*this);
        }

        template <typename GetOption>
        decltype(auto) get(GetOption option)
        {
            return option.get(*this);
        }

    };

}// namespace Pattern
