#pragma once

#include <iostream>
#include <vector>
#include "./base.h"
#include "./avatar.h"
#include <atomic>

namespace Pattern
{
    using namespace std::chrono_literals;


    class InGameSystem : 
            public updatable
    {
        std::atomic<bool> fstop{ false };
        std::vector<updatable*> ups{};

    public:
        InGameSystem();

        void processInput() noexcept;
        void update(std::chrono::milliseconds _ms) override;
        void render() noexcept;


        void resume();
        void stop();
        bool is_stopped() const noexcept;

        operator bool() const noexcept;
    };

}// namespace Pattern

namespace Pattern
{

    template <typename UnitType>
    class RateCalc
    {
    public:
        using unit_type = UnitType;

        // Exponential Weight Moving Average
        unit_type  ewma{};
    public:
        unit_type  calc(const unit_type  _elapsed)
        {
            const auto weighted = (ewma.count() * 5 + _elapsed.count() * 5) / 10;
            ewma = unit_type{ weighted };
            return ewma;
        }
    };


}// namespace Pattern


