#pragma once
#include "core.h"
#include "cs_threading.h"
#include "cs_time.h"
#include <string>

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
            ApplicationCloseEvent = 0, ApplicationPauseEvent, 
            ApplicationResumeEvent, AudioFinishedEvent,

            NetworkClientConnectedEvent, NetworkClientDisconnectedEvent
        };

        enum class InputEventType: uint32_t
        {
            KeyPressedEvent = 0, KeyHoldEvent, KeyReleasedEvent, 
            
            MouseButtonPressedEvent, MouseButtonHoldEvent,
            MouseButtonReleasedEvent, MouseMovedEvent,
            MouseScrollEvent, 
            
            GamepadConnectedEvent, GamepadDisconnectedEvent,
            GamepadButtonPressedEvent, GamepadButtonHoldEvent, 
            GamepadButtonReleasedEvent, GamepadAxisChangedEvent
        };
        
        enum class SceneEventType : uint32_t
        {
            SceneLoadedEvent, SceneSavedEvent
        };

        enum class AssetEventType : uint32_t
        {
            AssetLoadedEvent, AssetUnloadedEvent,
            AssetReloadedEvent
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
        static void dispatch(Event*);
    private:
        static Mutex m_lock;
    };

    class Event
    {
    public:
        virtual ~Event() = 0;

        virtual EventType type()   const = 0;
        virtual const char* name() const = 0;
        void dispatch();
    };

    class ApplicationCloseEvent : public Event
    {
    public:
        ApplicationCloseEvent() { time.start(); }
        virtual EventType type() const override { 
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Application),
            static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationCloseEvent));}
        
        virtual const char* name() const override { return "ApplicationCloseEvent"; }

        Time::stopwatch time;
    };

    class ApplicationPauseEvent : public ApplicationCloseEvent
    {
    public:
        EventType type() const override { 
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Application),
            static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationPauseEvent));}
        
        const char* name() const override { return "ApplicationPauseEvent"; }
    };

    class ApplicationResumeEvent : public Event
    {
    public:
        ApplicationResumeEvent() = default;

        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Application), 
            static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationResumeEvent));
        }
    };

    class KeyPressedEvent : public Event
    {
    public:
        virtual EventType type() const override { return EventType(static_cast<uint16_t>(EventType::EventCategories::Input), 
            static_cast<uint32_t>(EventType::InputEventType::KeyPressedEvent)); }
        virtual const char* name() const override { return "KeyPressedEvent"; }

        const char key{0};
    };

    class KeyHoldEvent : public KeyPressedEvent
    {
    public:
        EventType type() const override { return EventType(static_cast<uint16_t>(EventType::EventCategories::Input), 
            static_cast<uint32_t>(EventType::InputEventType::KeyHoldEvent)); }
        const char* name() const override { return "KeyHoldEvent"; }
    };

    class KeyReleasedEvent : public KeyPressedEvent
    {
    public:
        EventType type() const override { return EventType(static_cast<uint16_t>(EventType::EventCategories::Input), 
            static_cast<uint32_t>(EventType::InputEventType::KeyReleasedEvent)); }
        const char* name() const override { return "KeyReleasedEvent"; }
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseButtonPressedEvent));
        }

        virtual const char* name() const override { return "MouseButtonPressedEvent"; }
        uint16_t key{0};
    };

    class MouseButtonHoldEvent : public MouseButtonPressedEvent
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseButtonHoldEvent));
        }

        const char* name() const override { return "MouseButtonHoldEvent"; }
    };

    class MouseButtonReleasedEvent : public MouseButtonPressedEvent
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseButtonReleasedEvent));
        }

        virtual const char* name() const override { return "MouseButtonReleasedEvent"; }
    };

    class MouseMovedEvent : public Event
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseMovedEvent));
        }

        const char* name() const override { return "MouseMovedEvent"; }

        f32_t X_axis{0.0f}, Y_axis{0.0f};
    };

    class MouseScrollEvent : public Event
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseScrollEvent));
        }
        
        const char* name() const override { return "MouseScrollEvent"; }

        f32_t position{0.0f};
    };

    class GamepadConnectedEvent : public Event
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadConnectedEvent));
        }

        virtual const char* name() const override { return "GamepadConnectedEvent"; }

        std::string profile_name;
    };

    class GamepadDisconnectedEvent : public GamepadConnectedEvent
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadDisconnectedEvent));
        }

        const char* name() const override { return "GamepadDisconnectedEvent"; }

        std::string reason;
    };

    class GamepadButtonPressedEvent : public Event
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadButtonPressedEvent));
        }

        virtual const char* name() const override { return "GamepadButtonPressedEvent"; }

        uint16_t button{0};
    };

    class GamepadButtonHoldEvent : public GamepadButtonPressedEvent
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadButtonHoldEvent));
        }

        const char* name() const override { return "GamepadButtonHoldEvent"; }
    };

    class GamepadButtonReleasedEvent : public GamepadButtonPressedEvent
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadButtonReleasedEvent));
        }

        const char* name() const override { return "GamepadButtonReleasedEvent"; }
    };

    class GamepadAxisChangedEvent : public Event
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadAxisChangedEvent));
        }

        const char* name() const override { return "GamepadAxisChangedEvent"; }

        f32_t L_X_axis{0.0f}, L_Y_axis{0.0f},
              R_X_axis{0.0f}, R_Y_axis{0.0f};
    };

    
}