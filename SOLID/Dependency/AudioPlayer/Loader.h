#pragma once
#include <iostream>
#include "./Sound.h"

namespace Pattern
{
    class Loader
    {
    public:
        static Sound Load(const std::string& _fpath);
        static Sound Dispose(const std::string& _fpath);
    };

}// namespace Pattern
