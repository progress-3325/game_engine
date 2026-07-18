#include "cs_logging.h"
#include "cs_window.h"
#include "cs_events.h"

int main()
{
    cs::logger::log("This is an info message.", cs::L_CODE::C_INFO);
    cs::logger::log("This is a warning message.", cs::L_CODE::C_WARN);
    cs::logger::log("This is a debug message.", cs::L_CODE::C_DEBUG);
    
    cs::logger::log("This is an error message.", cs::L_CODE::C_ERROR_CONTINUE);
    
    cs::Window window{1000, 800, "Title"};

    while (!window.shouldClose())
    {
        window.pollEvents();
        window.swapBuffers();
        cs::EventDispatcher::process();
    }

    return 0;
}