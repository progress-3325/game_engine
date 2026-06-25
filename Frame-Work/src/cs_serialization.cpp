#include "cs_serialization.h"
#include <string>

namespace cs
{
    json_t project_config::proj_cfg = {
        {"Project Name", ""}, {"Company Name", ""},
        {"Version", {"Major", 0}, {"Minor", 0}, {"Patch", 0}, {"Suffix", std::string("")}}, 
        {"Engine version", {"Major", 0}, {"Minor", 0}, {"Patch", 0}, {"Suffix"}, std::string("")},
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

    void project_config::set_version(int major, int minor, int patch, const char* suffix)
    {
        proj_cfg.at("Version").at("Major") = major;
        proj_cfg.at("Version").at("Minor") = minor;
        proj_cfg.at("Version").at("Patch") = patch;
        proj_cfg.at("Version").at("Suffix") = suffix;
    }

    void project_config::set_engine_version(int major, int minor, int patch, const char* suffix)
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
}