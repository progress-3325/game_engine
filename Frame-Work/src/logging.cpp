#include "logging.h"
#include <iostream>
#include <string>
#include <chrono>
#include <cstring>
#include <fstream>
#include <unordered_map>


namespace cspace
{
    bool logger::debug = true;
    
    namespace detail
    {
        const std::unordered_map<L_CODE, const char*> color_codes = {
            {L_CODE::C_INFO, "\033[37;1m"},
            {L_CODE::C_WARN, "\033[33;1m"},
            {L_CODE::C_ERROR, "\033[31;1m"},
            {L_CODE::C_DEBUG, "\033[36;1m"},
            {L_CODE::C_RESET, "\033[0;21m"}
        };

        const std::unordered_map<L_CODE, const char*> string_codes = {
            {L_CODE::C_INFO, "<INFO>"},
            {L_CODE::C_WARN, "<WARN>"},
            {L_CODE::C_ERROR, "<ERROR>"},
            {L_CODE::C_DEBUG, "<DEBUG>"},
            {L_CODE::C_RESET, "<END_OF_STATEMENT"}
        };

        template<class duration>
        std::chrono::hh_mm_ss<duration> get_time()
        {
            auto now = std::chrono::system_clock::now();
            auto midnight = std::chrono::floor<std::chrono::days>(now);

            std::chrono::hh_mm_ss<duration> tod{std::chrono::duration_cast<duration>(now - midnight)};

            return tod;
        }

        template<class duration>
        std::string format_time(std::chrono::hh_mm_ss<duration> time)
        {
            std::string c = ":";
            std::string ret = std::string("[") + std::to_string(time.hours().count()) + c +
                std::to_string(time.minutes().count()) + c + std::to_string(time.seconds().count()) +
                std::string("]");
            
            return ret;
        }


    }

    using seconds = std::chrono::seconds;

    void logger::log(const char* msg, const L_CODE& c)
    {
        if (!debug && c == L_CODE::C_DEBUG) return;
        std::string cout_msg = std::string(detail::color_codes.at(c)) + detail::format_time<seconds>(detail::get_time<seconds>()) + 
             std::string(msg) + std::string(detail::color_codes.at(L_CODE::C_RESET));

        std::string ss_msg = std::string(detail::string_codes.at(c)) + detail::format_time<seconds>(detail::get_time<seconds>()) + 
             std::string(msg) + std::string(detail::string_codes.at(L_CODE::C_RESET));

        std::cout << cout_msg << std::endl;

        logged << ss_msg << "\n";
    }

    void logger::set_save_location(const char* loc)
    {
        save_location = new char[strlen(loc) + 1];
        strcpy(save_location, loc);
    }

    void logger::save()
    {
        std::ofstream file(std::string(save_location) + detail::format_time<seconds>(detail::get_time<seconds>()) + std::string(".log"), 
            std::ios_base::out);

        file.write(logged.str().c_str(), strlen(logged.str().c_str()));
        file.close();
    }
}