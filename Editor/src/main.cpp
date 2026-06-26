#include "cs_logging.h"
#include "application.h"

int main()
{
    cs::logger::log("This is an info message.", cs::L_CODE::C_INFO);
    cs::logger::log("This is a warning message.", cs::L_CODE::C_WARN);
    cs::logger::log("This is a debug message.", cs::L_CODE::C_DEBUG);
    
    Application::run();
    cs::logger::log("This is an error message.", cs::L_CODE::C_ERROR);
    
    return 0;
}