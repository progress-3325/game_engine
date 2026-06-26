#pragma once
#include "vendor/nlohmann/json.hpp"
#include <string>
#include <tuple>
#include <array>
#include <utility>

namespace cs
{
    using json_t = nlohmann::json;

    template<typename... Args>
    struct value_pack
    {
        std::tuple<Args...> values;
    };

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
        static void set_version(const int&, const int&, const int&, const char*);
        static void set_engine_version(const int&, const int&, const int&, const char*);
        static void set_start_scene(const char*);
        static void set_exec_name(const char*);

        static std::string get_proj_name();
        static std::string get_comp_name();
        static version_pack get_version();
        static version_pack get_engine_version();
        static std::string get_start_scene();
        static std::string get_exec_name();

        static void save_config(const char*);
        static void load_config(const char*);

        static void validate();
    private:
        static json_t proj_cfg;
    };

    struct game_config
    {
        template<typename T>
        static void set(const char*, const T&);

        template<typename... Args, std::size_t... I>
        static void set(const char*, const value_pack<Args...>&, const std::array<const char*, sizeof...(Args)>&);

        template<typename T>
        static T get(const char*);

        template<typename... Args, std::size_t... I>
        static value_pack<Args...> get(const char*, const std::array<const char*, sizeof...(Args)>&);

        static void save_config(const char*);
        static void load_config(const char*);

        static void validate(const json_t&);

    private:
        template<typename... Args, std::size_t... I>
        static void set_impl(const char*, const value_pack<Args...>&,
            const std::array<const char*, sizeof...(Args)>&,
            std::index_sequence<I...>
        );

        template<typename... Args, std::size_t... I>
        static value_pack<Args...> get_impl(const char*,
            const std::array<const char*, sizeof...(Args)>&,
            std::index_sequence<I...>
        );


        static json_t game_cfg;
    };

    struct serializer
    {
        static void save_cfg(const char*, const json_t&);
        static json_t load_cfg(const char*);
    };
}