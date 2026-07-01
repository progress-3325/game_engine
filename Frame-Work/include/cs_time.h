#pragma once

#include <chrono>
#include <string>
namespace cs
{
    class Time
    {
    public:
        using TimePoint = std::chrono::steady_clock::time_point;
        static inline float deltaTime() {return delta_time;}
        static inline double totalTime() {return total_time;}
        static std::string get_time_str();
        static std::string get_time_str(TimePoint tp);
    private:
        static float delta_time;
        static double total_time;
    public:
        class frame_timer
        {
        public:
            static void update();
            static double FPS();
        private:
            static TimePoint m_last_frame;
        };

        class stopwatch
        {
        public:
            void start();
            void stop();
            double readMilliseconds();
        
        private:
            TimePoint tmp_start;
            TimePoint tmp_end;
        };


    };
}