#include "logging.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "cs_time.h"
#include <cstring>
#include <fstream>
#include <unordered_map>


namespace cs
{
    bool logger::debug = true;
    std::mutex logger::log_mutex;
    std::stringstream logger::logged;
    char* logger::save_location = NULL;

    namespace detail
    {
        const std::unordered_map<L_CODE, const char*> color_codes = {
            {L_CODE::C_INFO, "\033[37;1m"},
            {L_CODE::C_WARN, "\033[33;1m"},
            {L_CODE::C_DEBUG, "\033[36;1m"},
            {L_CODE::C_RESET, "\033[0;21m"},
            {L_CODE::C_ERROR, "\033[31;1m"},
            {L_CODE::C_ERROR_CONTINUE, "\033[31;1m"},
        };

        const std::unordered_map<L_CODE, const char*> string_codes = {
            {L_CODE::C_INFO, "<INFO>"},
            {L_CODE::C_WARN, "<WARN>"},
            {L_CODE::C_DEBUG, "<DEBUG>"},
            {L_CODE::C_RESET, "<END_OF_STATEMENT"},
            {L_CODE::C_ERROR, "<ERROR>"},
            {L_CODE::C_ERROR_CONTINUE, "<ERROR>"},  
        };
    }

    using seconds = std::chrono::seconds;

    void logger::log(const char* msg, const L_CODE& c)
    {
        std::lock_guard<std::mutex> guard(log_mutex);

        if (!debug && c == L_CODE::C_DEBUG) return;

        std::string cout_msg = std::string(detail::color_codes.at(c)) + Time::get_time_str() + 
             std::string(msg) + std::string(detail::color_codes.at(L_CODE::C_RESET));

        std::string ss_msg = std::string(detail::string_codes.at(c)) + Time::get_time_str() + 
             std::string(msg) + std::string(detail::string_codes.at(L_CODE::C_RESET));

        std::cout << cout_msg << std::endl;

        logged << ss_msg << "\n";

        if (c == L_CODE::C_ERROR)
        {
            std::string j;
            std::cout << "Press [ENTER] to exit..." << std::endl;
            std::cin >> j;
            save();
            std::abort();
        }
    }

    void logger::set_save_location(const char* loc)
    {
        std::lock_guard<std::mutex> guard(log_mutex);
        delete[] save_location;
        save_location = new char[strlen(loc) + 1];
        strcpy(save_location, loc);
        save_location[strlen(loc)] = '\0';
    }

    void logger::save()
    {
        std::lock_guard<std::mutex> guard(log_mutex);
        if (save_location != NULL)
        {
            std::lock_guard<std::mutex> guard(log_mutex);
            std::ofstream file(std::string(save_location) + Time::get_time_str() + std::string(".log"), 
                std::ios_base::out);

            file.write(logged.str().c_str(), strlen(logged.str().c_str()));
            file.close();
        }
    }
}