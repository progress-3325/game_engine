#include "cs_serialization.h"
#include "cs_filesystem.h"
#include "logging.h"

namespace cs
{
    template<typename T>
    void Config::set(const char* property, T value)
    {
        this->cfg_file[property] = value;
    }

    Config& Config::operator=(const Config& other)
    {
        this->cfg_file = other.cfg_file;
        return *this;
    }

    void serializer::save(Config cfg, const char* path)
    {
        write_file(path, cfg.data().c_str());
    }

    Config serializer::load(const char* path)
    {
        Config cfg;
        try
        {
            cfg.cfg_file = nlohmann::json::parse(read_file(path));
        }
        catch (const nlohmann::json::parse_error& e)
        {
            logger::log(e.what(), L_CODE::C_ERROR);
        }
        return cfg;
    }
}