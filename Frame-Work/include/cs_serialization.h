#pragma once
#include "vendor/nlohmann/json.hpp"
#include <string>

namespace cs
{
    using json_t = nlohmann::json;

    template<typename... Args>
    struct value_pack;

    template<>
    struct value_pack<int, int, int, std::string>
    {
        int major, minor, patch;
        std::string suffix;
    };

    using version_pack = value_pack<int, int, int, std::string>;

    struct project_config
    {
        static void set_proj_name(const char*);
        static void set_comp_name(const char*);
        static void set_version(int, int, int, const char*);
        static void set_engine_version(int, int, int, const char*);
        static void set_start_scene(const char*);
        static void set_exec_name(const char*);

        static std::string get_proj_name();
        static std::string get_comp_name();
        static version_pack get_version();
        static version_pack get_engine_version();
        static std::string get_start_scene();
        static std::string get_exec_name();
    private:
        static json_t proj_cfg;
        friend class serializer;
    };

    struct game_config
    {

    private:
        static json_t game_cfg;
        friend class serializer;
    };

    class serializer
    {

    };
}