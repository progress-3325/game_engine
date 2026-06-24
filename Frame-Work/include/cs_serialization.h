#pragma once
#include "vendor/nlohmann/json.hpp"
#include <string>

namespace cs
{
    class Config
    {
    public:
        Config() = default;
        template<typename T>
        void set(const char*, T);
        std::string data() {return this->cfg_file.dump();}

        Config& operator=(const Config& other);
    private:
        nlohmann::json cfg_file = {
            {"ver_major", 0}, {"ver_minor", 0}, {"ver_bug", 0}, {"ver_suffix", std::string("")},
            {"project_name", std::string("")}, {"window_name", std::string("")}, {"width", 1920}, {"height", 1080},
            {"fullscreen", false}, {"borderless", false}
        };

        friend class Config;
        friend class serializer;
    };

    class serializer
    {
        static void save(Config, const char*);
        static Config load(const char*);
    };
}