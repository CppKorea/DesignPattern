// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File    : timer.hpp
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//  Updated : 16/09/05
//
//  Note
//      Simple stop watch class
//
//  Task
//      More types for time utility
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _MAGIC_TIMER_HPP_
#define _MAGIC_TIMER_HPP_

//#include <atomic>
#include <chrono>

namespace magic
{
    // - Note
    //      Stop watch class.
    //      Support `pick()` and `reset()` functionality
    template <typename Clock>
    class stop_watch
    {
    public:
        using clock_type    = Clock;
        using time_point    = typename clock_type::time_point;
        using duration      = typename clock_type::duration;

    private:
        //std::atomic<time_point> start = clock_type::now();
        time_point start = clock_type::now();

    public:
        template <typename UnitType = std::chrono::milliseconds>
        decltype(auto) pick() const noexcept
        {
            using namespace std::chrono;
            time_point curr = clock_type::now();

            //return duration_cast<UnitType>(current - start.load());
            return duration_cast<UnitType>(curr - start);
        };

        template <typename UnitType = std::chrono::milliseconds>
        decltype(auto) reset() noexcept
        {
            using namespace std::chrono;

            // end - start
            auto span = this->pick<UnitType>();

            // reset start time point
            //start.store(clock_type::now());
            start = clock_type::now();

            return span;
        }

    };



}// namespace magic

#endif
