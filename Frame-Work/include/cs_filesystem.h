#pragma once
#include <filesystem>

namespace cs
{
    bool exists(const char*);

    bool create_directory(const char*);

    bool remove(const char*);

    const char* read_file(const char*);

    const char* read_file_bin(const char*);

    bool write_file(const char*, const char*);

    bool write_file_bin(const char*, const char*);

    class Paths
    {
    public:
        static std::filesystem::path getEngine() {return engine;}
        static std::filesystem::path getLogs() {return logs;}
        static std::filesystem::path getAssets() {return assets;}
        static std::filesystem::path getConfig() {return config;}
    private:
        static std::filesystem::path engine;
        static std::filesystem::path logs;
        static std::filesystem::path assets;
        static std::filesystem::path config;
    };
}