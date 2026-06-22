#include "cs_filesystem.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <cstring>

namespace cs
{
    bool exists(const char* path)
    {
        return std::filesystem::exists(path);
    }

    bool create_directory(const char *path)
    {
        return std::filesystem::create_directory(path);
    }

    bool remove(const char* path)
    {
        return std::filesystem::remove(path);
    }

    const char* read_file(const char* path)
    {
        std::string ret;
        if (exists(path))
        {
            std::ifstream re_file(path, std::ifstream::in);

            re_file >> ret;
        }
        else
        {
            throw std::runtime_error("File doesn't exist");
        }
        
        char* dat = new char[ret.size() + 1];
        memcpy(dat, ret.c_str(), ret.size() + 1);
        dat[ret.size()] = '\0';
        return dat;
    }

    const char* read_file_bin(const char* path)
    {
        std::string ret;
        if (exists(path))
        {
            std::ifstream re_file(path, std::ifstream::binary);

            re_file >> ret;
        }
        else
        {
            throw std::runtime_error("File doesn't exist");
        }
        
        char* dat = new char[ret.size() + 1];
        memcpy(dat, ret.c_str(), ret.size() + 1);
        dat[ret.size()] = '\0';
        return dat;
    }


    bool write_file(const char* path, const char* data)
    {
        std::ofstream wr_file(path, std::ofstream::out);
        wr_file << data;
        wr_file.close();

        return exists(path);
    }


    bool write_file_bin(const char* path, const char* data)
    {
        std::ofstream wr_file(path, std::ofstream::binary);
        wr_file << data;
        wr_file.close();

        return exists(path);
    }
}