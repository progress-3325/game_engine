#pragma once
#include <sstream>
#include "core.h"
#include <mutex>

namespace cs
{
    enum class L_CODE : uint8_t
    {
        C_INFO = 0, C_WARN, C_DEBUG, C_RESET,
        C_ERROR, C_ERROR_CONTINUE
    };

    class logger
    {
    public:
        ~logger() { this->save(); }
        static void log(const char* msg, const L_CODE& c);
        static void set_save_location(const char* loc);
        static void save();
    public:
        static bool debug;
        static char* save_location;
    private:
        static std::stringstream logged;
        static std::mutex log_mutex;       
    };
}