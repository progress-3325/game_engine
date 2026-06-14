#pragma once
#include <sstream>
#include <unordered_map>

namespace cspace
{
    enum class L_CODE : unsigned char
    {
        C_INFO = 0, C_WARN, C_ERROR, C_DEBUG, C_RESET
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
    };
}