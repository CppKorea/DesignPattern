#include "./skills.h"
#include "./avatar.h"

namespace Pattern
{
    void Fly::update(std::chrono::milliseconds _time)
    {
        this->cool -= _time;
    }

    bool Fly::isReady()
    {        
        const auto HP = avatar.hp;
        const auto Height = avatar.pos.y;

        if (HP != 0 && Height <= 0) {
            return true;
        }
        return false;
    }

    bool Fly::activate()
    {
        this->cool = std::chrono::milliseconds{ 1000 };

        avatar.pos.y = 200;
        return true;
    }

}
