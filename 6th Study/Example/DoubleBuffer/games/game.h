#pragma once
#include "./FrameBuffer.h"
#include "./IOSystem.h"
#include "./timer.hpp"

namespace Pattern
{
    using namespace std::chrono_literals;

    // - Note
    //      Double buffer provider module
    // - Pattern
    //      Double Buffer
    template <typename BufferType>
    class BufferModule
    {
    private:
        BufferType buffers[2];
        BufferType* pcurr = buffers + 0;
        BufferType* pnext = buffers + 1;

    public:
        BufferModule() = default;

        const BufferType& current() const noexcept
        {
            return *pcurr;
        }

        const BufferType& next() const noexcept
        {
            return *pnext;
        }

        BufferType& next() noexcept
        {
            return *pnext;
        }

        void change() noexcept
        {
            std::swap(pcurr, pnext);
        }

    };



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


    template <typename BufferType>
    class InGameSystem:
            BufferModule<BufferType>
    {
        int counter{ 1 };
    public:
        InGameSystem()
        {
            this->next()[{1, 0}] = 0xAA;
            this->change();
            this->next()[{1, 0}] = 0xBB;
            this->change();
        }

        void update(std::chrono::milliseconds _ms) 
        {
            std::cout << "update time "<< _ms.count() << " ms... "<< std::endl;
         
            // Do stuff...
            auto& buffer = this->next();
            buffer[{0, 0}] = counter++;

            // Swap the buffer
            this->change();
        }

        decltype(auto) buffer() const noexcept 
        {
            return this->current();
        }
    };

}// namespace Pattern

