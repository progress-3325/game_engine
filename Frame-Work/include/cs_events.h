#pragma once
#include "core.h"
#include "cs_threading.h"
#include "cs_time.h"
#include <string>
#include <GLFW/glfw3.h>

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
            KeyPressedEvent = 0, KeyReleasedEvent, 
            
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

    namespace Input
    {
        enum class Keys : uint16_t
        {
            KeySpace = GLFW_KEY_SPACE, 
            KeyApostrophe = GLFW_KEY_APOSTROPHE,
            KeyComma = GLFW_KEY_COMMA, KeyDash, KeyPeriod, KeySlash,


            Key0, Key1, Key2, Key3, Key4,
            Key5, Key6, Key7, Key8, Key9,

            KeySemicolon = GLFW_KEY_SEMICOLON, 
            KeyEqual = GLFW_KEY_EQUAL,
            
            KeyA = GLFW_KEY_A, KeyB, KeyC, KeyD,
            KeyE, KeyF, KeyG, KeyH, KeyI, KeyJ, KeyK,
            KeyL, KeyM, KeyN, KeyO, KeyP, KeyQ,
            KeyR, KeyS, KeyT, KeyU, KeyV, KeyW, KeyX,
            KeyY, KeyZ, KeyLBracket, KeyBSlash,KeyRBracket,
            KeyGrave = GLFW_KEY_GRAVE_ACCENT,

            KeyESC = GLFW_KEY_ESCAPE, KeyEnter, KeyTab,
            KeyBackspace, KeyInsert, KeyDelete, KeyRight,
            KeyLeft, KeyDown, KeyUp, KeyPageUp, KeyPageDown,
            KeyHome, KeyEnd, 
            
            KeyCapsLock = GLFW_KEY_CAPS_LOCK,
            KeyScrollLock, KeyNumLock, KeyPrint, KeyPause,
            
            KeyF1 = GLFW_KEY_F1, KeyF2, KeyF3, KeyF4, KeyF5,
            KeyF6, KeyF7, KeyF8, KeyF9, KeyF10, KeyF11, KeyF12,
            KeyF13, KeyF14, KeyF15, KeyF16, KeyF17, KeyF18,
            KeyF19, KeyF20, KeyF21, KeyF22, KeyF23, KeyF24,
            KeyF25,

            KeyKPDecimal = GLFW_KEY_KP_DECIMAL, KeyKPDivide,
            KeyKPMultiply, KeyKPSubtract, KeyKPAdd, KeyKPEnter,
            KeyKPEqual,

            KeyLShift = GLFW_KEY_LEFT_SHIFT, KeyLCTRL,
            KeyLAlt, LeyLSuper, KeyRShift, KeyRCTRL, KeyRAlt,
            KeyRSupre, KeyMenu
        };

        enum class MouseButtons : uint16_t
        {
            MouseBLeft = GLFW_MOUSE_BUTTON_LEFT, MouseBRight,
            MouseBMiddle, MouseB4, MouseB5, MouseB6, MouseB7, 
            MouseB8
        };

        enum class JoystickDir : uint16_t
        {
            Joy1 = GLFW_JOYSTICK_1, Joy2, Joy3, Joy4,
            Joy5, Joy6, Joy7, Joy8, Joy9, Joy10, Joy11,
            Joy12, Joy13, Joy14, Joy15, Joy16
        };

        enum class GamepadButtons : uint16_t
        {
            GamepadBA = GLFW_GAMEPAD_BUTTON_A, GamepadBB, 
            GamepadBX, GamepadBY, GamepadLBumper, GamepadRBumper,
            GamepadBack, GamepadStart, GamepadGuide, GamepadLThumb,
            GamepadRThumb, GamepadDPadUp, GamepadDPadRight,
            GamepadDPadDown, GamepadDPadLeft
        };

        enum class GamepadAxis : uint16_t
        {
            GamepadAxisLX = GLFW_GAMEPAD_AXIS_LEFT_X, 
            GamepadAxisLY, GamepadAxisRX, GamepadRY, 
            GamepadLTrigger, GamepadRTrigger
        };

        template<Keys key>
        bool isKeyPressed();
        template<Keys key>
        bool isKeyHeld();
        template<Keys key>
        bool isKeyReleased();
        template<Keys key>
        double keyHeldTime();
    }

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual EventType type()   const = 0;
        virtual cstring name() const = 0;
        void dispatch();
        virtual void execute()     const = 0;
    };

    class ApplicationCloseEvent : public Event
    {
    public:
        virtual EventType type() const override { 
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Application),
            static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationCloseEvent));}
        
        virtual cstring name() const override { return "ApplicationCloseEvent"; }

        virtual void execute() const override;
    };

    class ApplicationPauseEvent : public ApplicationCloseEvent
    {
    public:
        EventType type() const override { 
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Application),
            static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationPauseEvent));}
        
        cstring name() const override { return "ApplicationPauseEvent"; }
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
        KeyPressedEvent() = default;
        KeyPressedEvent(const Input::Keys& p_key) : key(p_key) {}

        virtual EventType type() const override { return EventType(static_cast<uint16_t>(EventType::EventCategories::Input), 
            static_cast<uint32_t>(EventType::InputEventType::KeyPressedEvent)); }
        virtual cstring name() const override { return "KeyPressedEvent"; }

        Input::Keys key{0};

        KeyPressedEvent& operator=(const KeyPressedEvent& other)
        {
            this->key = other.key;
        }

        virtual void execute() const override;
    };

    class KeyReleasedEvent : public KeyPressedEvent
    {
    public:
        KeyReleasedEvent(const Input::Keys& p_key) : key(p_key) {}
        EventType type() const override { return EventType(static_cast<uint16_t>(EventType::EventCategories::Input), 
            static_cast<uint32_t>(EventType::InputEventType::KeyReleasedEvent)); }
        cstring name() const override { return "KeyReleasedEvent"; }
        
        Input::Keys key{0};

        void execute() const override;
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        MouseButtonPressedEvent() = default;
        MouseButtonPressedEvent(const Input::MouseButtons& p_button) : button(p_button) {}
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseButtonPressedEvent));
        }

        virtual cstring name() const override { return "MouseButtonPressedEvent"; }
        Input::MouseButtons button{0};

        virtual void execute() const override;
    };

    class MouseButtonReleasedEvent : public MouseButtonPressedEvent
    {
    public:
        MouseButtonReleasedEvent(const Input::MouseButtons& p_button) : button(p_button) {}
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseButtonReleasedEvent));
        }

        virtual cstring name() const override { return "MouseButtonReleasedEvent"; }
        Input::MouseButtons button{0};

        void execute() const override;
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(f64_t xPos, f64_t yPos) : X_axis(xPos), Y_axis(yPos) {}
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseMovedEvent));
        }

        cstring name() const override { return "MouseMovedEvent"; }

        void execute() const override;

        f64_t X_axis{0.0f}, Y_axis{0.0f};
    };

    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(f64_t xPos, f64_t yPos) : position_x(xPos), position_y(yPos) {}
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::MouseScrollEvent));
        }
        
        cstring name() const override { return "MouseScrollEvent"; }

        void execute() const override;

        f64_t position_x{0.0f}, position_y{0.0f};
    };

    class GamepadConnectedEvent : public Event
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadConnectedEvent));
        }

        virtual cstring name() const override { return "GamepadConnectedEvent"; }

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

        cstring name() const override { return "GamepadDisconnectedEvent"; }

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

        virtual cstring name() const override { return "GamepadButtonPressedEvent"; }

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

        cstring name() const override { return "GamepadButtonHoldEvent"; }
    };

    class GamepadButtonReleasedEvent : public GamepadButtonPressedEvent
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadButtonReleasedEvent));
        }

        cstring name() const override { return "GamepadButtonReleasedEvent"; }
    };

    class GamepadAxisChangedEvent : public Event
    {
    public:
        EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Input),
            static_cast<uint32_t>(EventType::InputEventType::GamepadAxisChangedEvent));
        }

        cstring name() const override { return "GamepadAxisChangedEvent"; }

        f32_t L_X_axis{0.0f}, L_Y_axis{0.0f},
              R_X_axis{0.0f}, R_Y_axis{0.0f};
    };

    class SceneLoadedEvent : public Event
    {
    public:
        virtual EventType type() const override
        {
            return EventType(static_cast<uint16_t>(EventType::EventCategories::Scene),
            static_cast<uint32_t>(EventType::SceneEventType::SceneLoadedEvent));
        }

        virtual cstring name() const override { return "SceneLoadedEvent"; }


    };






    class EventDispatcher
    {
    public:
        static void dispatch(Event*);
        static void process();
    private:
        static Mutex m_lock;
    };










    
}