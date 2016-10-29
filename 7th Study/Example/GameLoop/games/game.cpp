#pragma once

#include "./game.h"
#include <thread>
#include <iostream>
using namespace std;
using namespace std::chrono_literals;

namespace Pattern
{
    InGameSystem::InGameSystem()
    {
        auto* a = new Avatar{};
        this->ups.push_back(a);
    }


    void InGameSystem::processInput() noexcept
    {
        std::this_thread::sleep_for(1ms);
    }

    void InGameSystem::update(std::chrono::milliseconds _ms)
    {
        for (auto elem : this->ups) {
            elem->update(_ms);
        }
    }

    void InGameSystem::render() noexcept
    {
        std::this_thread::sleep_for(14ms);
    }

    void InGameSystem::resume()
    {
        fstop = false;
    }

    void InGameSystem::stop() {
        fstop = true;
    }

    bool InGameSystem::is_stopped() const noexcept
    {
        return fstop == true;
    }

    InGameSystem::operator bool() const noexcept
    {
        return this->is_stopped() == false;
    }

}// namespace Pattern
