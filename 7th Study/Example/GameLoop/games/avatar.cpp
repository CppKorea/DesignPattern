#include "./avatar.h"
#include "./skills.h"
namespace Pattern
{
    Avatar::Avatar()
    {
        this->setSkill(new Fly{ *this });
    }

    void Avatar::update(std::chrono::milliseconds _time)
    {
        if (skill) {
            skill->update(_time);
        }
    }

}// namespace Pattern
