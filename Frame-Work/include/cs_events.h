#pragma once
#include "core.h"
#include "cs_threading.h"

namespace cs
{
    struct EventType
    {
        EventType() = default;
        EventType(const uint16_t& p_category, const uint32_t& p_type) : category(p_category), type(p_type) {}
        EventType(const EventType& p_event) : category(p_event.category), type(p_event.type) {}

        EventType& operator=(const EventType& other)
        {
            this->category = other.category;
            this->type = other.type;
            return *this;
        }

        uint16_t category{5};
        uint32_t type{0};

        enum class EventCategories : uint16_t
        {
            Application = 0, Input, Scene, Asset, Physics, NullEventType
        };

        enum class ApplicationEventType : uint32_t
        {

        };

        enum class InputEventType: uint32_t
        {

        };
        
        enum class SceneEventType : uint32_t
        {

        };

        enum class AssetEventType : uint32_t
        {

        };

        enum class PhysicsEventType : uint32_t
        {

        };

        enum class NullEventType : uint32_t
        {

        };
    };

    class EventDispatcher
    {
    public:
        static void dispatch(const EventType&);
    private:
        static Mutex m_lock;
    };
}