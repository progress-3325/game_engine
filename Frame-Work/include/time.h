#pragma once

namespace cs
{
    class Time
    {
    public:
        static float deltaTime() {return delta_time;}
        static double totalTime() {return total_time;}
    private:
        static float delta_time;
        static float total_time;
    };
}