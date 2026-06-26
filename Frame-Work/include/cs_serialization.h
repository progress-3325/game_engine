#pragma once
#include "vendor/nlohmann/json.hpp"
#include <string>
#include <tuple>
#include <array>
#include <utility>
#include "core.h"
#include <random>

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

    template<typename T, std::size_t I>
    struct v_array
    {
        T arr[I];
    };

    template<>
    struct v_array<uint64_t, 2>
    {
        uint64_t high;
        uint64_t low;
    };

    using hex_128bit = v_array<uint64_t, 2>;

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


    class UUID
    {
    public:
        UUID() = default;
        UUID(const hex_128bit& array) : m_high(array.high), m_low(array.low) {}
        UUID(const UUID& other) : m_high(other.high()), m_low(other.low()) {}
        UUID(const uint64_t& p_high, const uint64_t& p_low) : m_high(p_high), m_low(p_low) {}


        uint64_t high() const { return this->m_high; }
        uint64_t low() const { return this->m_low; }

        std::string to_string() const;

        UUID& operator=(const hex_128bit& array)
        {
            this->m_high = array.high;
            this->m_low = array.low;
            return *this;
        }

        UUID& operator=(const UUID& other)
        {
            this->m_high = other.high();
            this->m_low = other.low();
            return *this;
        }

        bool operator==(const UUID& other)
        {
            return this->m_high == other.high() && this->m_low == other.low();
        }

        bool operator!=(const UUID& other)
        {
            return !(*this == other);
        }

        static UUID from_string(const std::string&);

    private:
        uint64_t m_high{};
        uint64_t m_low{};
    };


    class UUID_gen
    {
    public:
        static UUID generate();

    private:
    };
}

namespace std
{
    template<>
    struct hash<cs::UUID>
    {
        size_t operator()(const cs::UUID& id) const
        {
            return id.high() ^ id.low();
        }
    };
}