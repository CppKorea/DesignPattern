#pragma once

#include "./base.h"
namespace Pattern
{
    using namespace std::chrono_literals;
    class Avatar;

    class Skill : 
            public updatable
    {
    protected:
        Avatar& avatar;
    public:
        explicit Skill(Avatar& _avatar) :
            avatar{ _avatar }
        {}

        //void update(std::chrono::milliseconds _time);
        virtual bool isReady() = 0;
        virtual bool activate() = 0;

    };


    class Fly : 
            public Skill
    {
        std::chrono::milliseconds cool = 1000ms;
    public:
        explicit Fly(Avatar& _avatar) :
            Skill{_avatar}
        {}

        void update(std::chrono::milliseconds _time) override;
        virtual bool isReady() override;
        virtual bool activate() override;
    };




}

