#include "cs_serialization.h"
#include <sstream>
#include <string>
#include "cs_logging.h"
#include "cs_assert.h"

namespace cs
{
    json_t project_config::proj_cfg = {
        {"Project Name", ""}, {"Company Name", ""},
        {"Version", {
            {"Major", 0}, {"Minor", 0}, 
            {"Patch", 0}, {"Suffix", std::string("")}
            }}, 
        {"Engine version", {{"Major", 0}, {"Minor", 0}, {"Patch", 0}, {"Suffix"}, std::string("")}},
        {"Start Scene", std::string("")}, {"Exec Name", std::string("")}
    };

    void project_config::set_proj_name(const char* name)
    {
        proj_cfg.at("Project Name") = name;
    }

    void project_config::set_comp_name(const char* name)
    {
        proj_cfg.at("Project Name") = name;
    }

    void project_config::set_version(const int& major, const int& minor, const int& patch, const char* suffix)
    {
        proj_cfg.at("Version").at("Major") = major;
        proj_cfg.at("Version").at("Minor") = minor;
        proj_cfg.at("Version").at("Patch") = patch;
        proj_cfg.at("Version").at("Suffix") = suffix;
    }

    void project_config::set_engine_version(const int& major, const int& minor, const int& patch, const char* suffix)
    {
        proj_cfg.at("Engine").at("Major") = major;
        proj_cfg.at("Engine").at("Minor") = minor;
        proj_cfg.at("Engine").at("Patch") = patch;
        proj_cfg.at("Engine").at("Suffix") = suffix;
    }

    void project_config::set_start_scene(const char* path)
    {
        proj_cfg.at("Start Scene") = path;
    }

    void project_config::set_exec_name(const char* name)
    {
        proj_cfg.at("Exec Name") = name;
    }

    std::string project_config::get_proj_name()
    {
        if (proj_cfg.at("Project Name") == std::string("")) return "Project";
        return proj_cfg.at("Project Name");
    }

    std::string project_config::get_comp_name()
    {

        if (proj_cfg.at("Company Name") == std::string("")) return "Company";
        return proj_cfg.at("Company Name");
    }

    version_pack project_config::get_version()
    {
        if (proj_cfg.at("Version").at("Major") == 0 && proj_cfg.at("Version").at("Minor") == 0 
            && proj_cfg.at("Version").at("Patch") == 0 && proj_cfg.at("Version").at("Suffix") == std::string(""))
            return version_pack{0, 0, 0, ""};
        return version_pack{proj_cfg.at("Version").at("Major"), proj_cfg.at("Version").at("Minor"),
            proj_cfg.at("Version").at("Patch"), proj_cfg.at("Version").at("Suffix")};
    }

    version_pack project_config::get_engine_version()
    {
        if (proj_cfg.at("Engine").at("Major") == 0 && proj_cfg.at("Engine").at("Minor") == 0 && 
            proj_cfg.at("Engine").at("Patch") == 0 && proj_cfg.at("Engine").at("Suffix") == std::string(""))
            return version_pack{0, 0, 0, ""};
        return version_pack{proj_cfg.at("Engine").at("Major"), proj_cfg.at("Engine").at("Minor"), 
            proj_cfg.at("Engine").at("Patch"), proj_cfg.at("Engine").at("Suffix")};
    }

    std::string project_config::get_start_scene()
    {
        if (proj_cfg.at("Start Scene") == std::string("")) return "main.scene";
        return proj_cfg.at("Start Scene");
    }

    std::string project_config::get_exec_name()
    {
        if (proj_cfg.at("Exec Name") == std::string("")) return "Game";
        return proj_cfg.at("Exec Name");
    }

    void project_config::save_config(const char *path)
    {
        serializer::save_cfg(path, proj_cfg);
    }

    void project_config::load_config(const char *path)
    {
        proj_cfg = serializer::load_cfg(path);

        validate();
    }

    namespace detail
    {
        const json_t default_proj_cfg = {
            {"Project Name", "Project"}, {"Company Name", "Company"},
            {"Version", {{"Major", 0}, {"Minor", 0}, {"Patch", 0}, {"Suffix", std::string("not indev")}}}, 
            {"Engine version", {{"Major", 0}, {"Minor", 0}, {"Patch", 0}, {"Suffix", std::string("indev")}}},
            {"Start Scene", std::string("")}, {"Exec Name", std::string("")}
        };
    }

    void project_config::validate()
    {
        for (const auto& [key, value] : proj_cfg.items())
        {
            if (!value.is_object() && value.is_string())
            {
                if (value.is_null()) proj_cfg.at(key) = detail::default_proj_cfg.at(key);

                std::string s_value = std::string(key) + std::string(": ") + std::string(value.dump());
                logger::log(s_value.c_str(), L_CODE::C_DEBUG);
            }
            else if (value.is_string())
            {
                for (const auto& [ar_key, ar_value] : value.items())
                {
                    if (ar_value.is_null() || (!ar_value.is_string() && ar_key != "Suffix")) proj_cfg.at(key).at(ar_key) = detail::default_proj_cfg.at(key).at(ar_key);
                    
                    std::string s_value = std::string(ar_key) + std::string(": ") + std::string(ar_value.dump());
                    logger::log(s_value.c_str(), L_CODE::C_DEBUG);
                }
            }
        }
    }

    template<typename T>
    void game_config::set(const char* key, const T& value)
    {
        game_cfg[key] = value;
    }

    template<typename... Args, std::size_t... I>
    void game_config::set_impl(const char* key, const value_pack<Args...>& values,
        const std::array<const char*, sizeof...(Args)>& keys,
        std::index_sequence<I...>
    )
    {
        (
            (game_cfg[key][keys[I]] = std::get<I>(values.values)), ...
        );
    }

    template<typename... Args, std::size_t... I>
    void game_config::set(const char* key, const value_pack<Args...>& values, const std::array<const char*, sizeof...(Args)>& keys)
    {
        set_impl(key, values, keys, std::index_sequence_for<Args...>{});
    }


    template<typename T>
    T game_config::get(const char* key)
    {
        return game_cfg.get<T>(key);
    }

    template<typename... Args, std::size_t... I>
    value_pack<Args...> game_config::get_impl(const char* key,
        const std::array<const char*, sizeof...(Args)>& keys,
        std::index_sequence<I...>
    )
    {
        CS_ASSERT_MSG(game_cfg.at(key).is_object(), "If this was triggered you tried to get multiple values from a parameter that only has 1");
        CS_ASSERT_MSG((game_cfg.at(key).contains(keys[I]) && ...), "If this is triggered you tried to get values that don't exist in this object!");

        value_pack<Args...> ret_values;
        (
            (std::get<I>(ret_values.values) = game_cfg[key][keys[I]].template get<std::tuple_element_t<I, decltype(ret_values.values)>>()), ...
        );

        return ret_values;
    }

    template<typename... Args, std::size_t... I>
    value_pack<Args...> game_config::get(const char* key, const std::array<const char*, sizeof...(Args)>& keys)
    {
        return get_impl(key, keys, std::index_sequence_for<Args...>{});
    }

    void game_config::save_config(const char* path)
    {
        serializer::save_cfg(path, game_cfg);
    }

    void game_config::load_config(const char* path)
    {
        game_cfg = serializer::load_cfg(path);
    }

    void game_config::validate(const json_t& default_cfg)
    {
        for (const auto& [key, value] : default_cfg.items())
        {
            if (!default_cfg.at(key).is_object())
            {
                if (game_cfg.contains(key)) continue;
                else game_cfg[key] = value;
            }
            else
            {
                for (const auto& [ar_key, ar_value] : default_cfg.at(key).items())
                {
                    if (game_cfg.contains(key) && game_cfg.at(key).contains(ar_key)) continue;
                    else game_cfg[key][ar_key] = ar_value;
                }
            }
        }
    }

    std::string UUID::to_string() const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << this->m_high << std::setw(16) << std::setfill('0') << this->m_low;
        return ss.str();
    }

    UUID UUID::from_string(const std::string& id)
    {
        uint64_t high = std::stoull(id.substr(0, 16), nullptr, 16);
        uint64_t low = std::stoull(id.substr(16, 16), nullptr, 16);

        return v_array<uint64_t, 2>{high, low};
    }

    UUID UUID_gen::generate()
    {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        return UUID(engine(), engine());
    }
}