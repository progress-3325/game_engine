#pragma once

#include <chrono>
#include <string>
namespace cs
{
    class Time
    {
    public:
        static inline float deltaTime() {return delta_time;}
        static inline double totalTime() {return total_time;}
        static std::string get_time_str();    
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
            static std::chrono::steady_clock::time_point m_last_frame;
        };

        class stopwatch
        {
        public:
            void start();
            void stop();
            double readMilliseconds();
        
        private:
            std::chrono::steady_clock::time_point tmp_start;
            std::chrono::steady_clock::time_point tmp_end;
        };
    };
}