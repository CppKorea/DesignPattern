#pragma once

#include "./base.h"
#include "./skills.h"

namespace Pattern
{

    class Avatar : 
            public updatable
    {
        Skill* skill = nullptr;

    public:
        i32     hp{ 100 }, mp{ 20 };
        Pos2D   pos;
    public:
        Avatar();

        void update(std::chrono::milliseconds _time) override;

        void setSkill(Skill* _skill)
        {
            if (_skill != nullptr) {
                skill = _skill;
            }
        }

        bool useSkill()
        {
            if (skill && skill->isReady()) {
                skill->activate();
                return true;
            }
            return false;
        }

    };

}// namespace Pattern
