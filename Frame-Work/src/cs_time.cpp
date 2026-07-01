#include "cs_time.h"
#include <chrono>
#include <string>

namespace cs
{
    void Time::frame_timer::update()
    {
        auto now = std::chrono::steady_clock::now();

        Time::delta_time = std::chrono::duration<float>(now - m_last_frame).count();
        Time::total_time += Time::delta_time;
        m_last_frame = now;
    }

    void Time::stopwatch::start()
    {
        this->tmp_start = std::chrono::steady_clock::now();
    }

    void Time::stopwatch::stop()
    {
        this->tmp_end = std::chrono::steady_clock::now();
    }

    double Time::stopwatch::readMilliseconds()
    {
        return std::chrono::duration<double>(this->tmp_end - this->tmp_start).count();
    }

    std::string Time::get_time_str()
    {
        auto now = std::chrono::system_clock::now();
        auto midnight = std::chrono::floor<std::chrono::days>(now);

        std::chrono::hh_mm_ss<std::chrono::seconds> tod{std::chrono::duration_cast<std::chrono::seconds>(now - midnight)};

        std::string colon = ":";
        std::string ret = std::string("[") + std::to_string(tod.hours().count()) + colon +
            std::to_string(tod.minutes().count()) + colon + std::to_string(tod.seconds().count()) +
            std::string("]");
        
        return ret;
    }

    double Time::frame_timer::FPS()
    {
        return 1.0f / Time::deltaTime();
    }

    std::string Time::get_time_str(TimePoint tp)
    {
        auto midnight = std::chrono::floor<std::chrono::days>(tp);

        std::chrono::hh_mm_ss<std::chrono::seconds> tod{std::chrono::duration_cast<std::chrono::seconds>(tp - midnight)};

        std::string colon = ":";

        std::string ret = std::string("[") + std::to_string(tod.hours().count()) + colon +
            std::to_string(tod.minutes().count()) + colon + std::to_string(tod.seconds().count()) +
            std::string("]");

        return ret;
    }
}