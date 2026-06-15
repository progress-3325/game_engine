#include "logging.h"
#include "application.h"

int main()
{
    cspace::logger::log("This is an info message.", cspace::L_CODE::C_INFO);
    cspace::logger::log("This is a warning message.", cspace::L_CODE::C_WARN);
    cspace::logger::log("This is an error message.", cspace::L_CODE::C_ERROR);
    cspace::logger::log("This is a debug message.", cspace::L_CODE::C_DEBUG);

    Application::run();

    return 0;
}