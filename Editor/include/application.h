#pragma once

class Application
{
public:
    static void run();
    static bool is_running() { return running; }
private:
    static bool running;
};