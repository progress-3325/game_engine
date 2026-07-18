#include "cs_events.h"
#include "cs_logging.h"
#include <deque>
#include <memory>
#include <unordered_map>
#include <array>
#include "cs_time.h"

static constexpr size_t key_amount = 120;
static constexpr size_t mouse_button_amount = 8;

namespace cs
{
    Mutex EventDispatcher::m_lock{};
    namespace detail
    {
        struct ev_storer
        {
            static std::deque<std::unique_ptr<Event>> events;
        };
        std::deque<std::unique_ptr<Event>> ev_storer::events{};
    }

    void EventDispatcher::dispatch(Event* ev)
    {
        Guard lock(m_lock);
        logger::log("Dispatching Event!", L_CODE::C_DEBUG);

        detail::ev_storer::events.emplace_back(ev);

        logger::log("Event Dispatched!", L_CODE::C_DEBUG);
    }

    void Event::dispatch()
    {
        EventDispatcher::dispatch(this);
    }

    namespace detail
    {
        struct key_pressed
        {
            static std::array<bool, key_amount> is_pressed;
            static std::array<bool, key_amount> is_held;
            static std::array<bool, key_amount> is_released;
            static std::array<Time::stopwatch, key_amount> heldTime;

            static std::array<bool, mouse_button_amount> mouse_is_pressed;
            static std::array<bool, mouse_button_amount> mouse_is_held;
            static std::array<bool, mouse_button_amount> mouse_is_released;
            static std::array<Time::stopwatch, mouse_button_amount> mouse_heldTime;
            static f64_t mouse_pos_x, mouse_pos_y, mouse_scroll_x, mouse_scroll_y;
        };

        std::array<bool, key_amount> key_pressed::is_pressed{};
        std::array<bool, key_amount> key_pressed::is_held{};
        std::array<bool, key_amount> key_pressed::is_released{};
        std::array<Time::stopwatch, key_amount> key_pressed::heldTime{};

        std::array<bool, mouse_button_amount> key_pressed::mouse_is_pressed{};
        std::array<bool, mouse_button_amount> key_pressed::mouse_is_held{};
        std::array<bool, mouse_button_amount> key_pressed::mouse_is_released{};
        std::array<Time::stopwatch, mouse_button_amount> key_pressed::mouse_heldTime{};
        
        


        f64_t key_pressed::mouse_pos_x{0.0f}, key_pressed::mouse_pos_y{0.0f}, key_pressed::mouse_scroll_x{0.0f}, key_pressed::mouse_scroll_y{0.0f};

    }


    template<Input::Keys key>
    bool Input::isKeyPressed()
    {
        return detail::key_pressed::is_pressed[static_cast<uint16_t>(key)];
    }

    template<Input::Keys key>
    bool Input::isKeyHeld()
    {
        return detail::key_pressed::is_held[static_cast<uint16_t>(key)];
    }

    template<Input::Keys key>
    bool Input::isKeyReleased()
    {
        return detail::key_pressed::is_released[static_cast<uint16_t>(key)];
    }

    template<Input::Keys key>
    double Input::keyHeldTime()
    {
        return detail::key_pressed::heldTime[static_cast<uint16_t>(key)].readMilliseconds();
    }

    template<Input::MouseButtons button>
    bool isButtonPressed()
    {
        return detail::key_pressed::mouse_is_pressed[static_cast<uint16_t>(button)];
    }


    void KeyPressedEvent::execute() const
    {
        const auto index = static_cast<uint16_t>(this->key);

        detail::key_pressed::is_pressed[index] = true;
        detail::key_pressed::is_held[index] = true;
        detail::key_pressed::heldTime[index].start();

        logger::log(this->name(), L_CODE::C_DEBUG);
    }

    void KeyReleasedEvent::execute() const
    {
        const auto index = static_cast<uint16_t>(this->key);

        detail::key_pressed::is_held[index] = false;
        detail::key_pressed::heldTime[index].stop();
        detail::key_pressed::is_released[index] = true;
        logger::log(this->name(), L_CODE::C_DEBUG);
        logger::log(std::string(std::string("Key pressed for ") + std::to_string(detail::key_pressed::heldTime[index].readMilliseconds())).c_str(), L_CODE::C_DEBUG);
    }

    void MouseButtonPressedEvent::execute() const
    {
        const auto index = static_cast<uint16_t>(this->button);

        detail::key_pressed::is_pressed[index] = true;
        detail::key_pressed::is_held[index] = true;
        detail::key_pressed::heldTime[index].start();
        logger::log(this->name(), L_CODE::C_DEBUG);
    }

    void MouseButtonReleasedEvent::execute() const
    {
        const auto index = static_cast<uint16_t>(this->button);

        detail::key_pressed::is_held[index] = false;
        detail::key_pressed::is_released[index] = true;
        detail::key_pressed::heldTime[index].stop();
        logger::log(this->name(), L_CODE::C_DEBUG);
    }

    void MouseMovedEvent::execute() const
    {
        detail::key_pressed::mouse_pos_x = this->X_axis;
        detail::key_pressed::mouse_pos_y = this->Y_axis;
        logger::log(this->name(), L_CODE::C_DEBUG);
    }

    void MouseScrollEvent::execute() const
    {
        detail::key_pressed::mouse_scroll_x = this->position_x;
        detail::key_pressed::mouse_scroll_y = this->position_y;
        logger::log(this->name(), L_CODE::C_DEBUG);
    }


    void EventDispatcher::process()
    {
        Guard lock(m_lock);
        using namespace detail;

        key_pressed::is_pressed.fill(false);
        key_pressed::is_released.fill(false);

        while (!ev_storer::events.empty())
        {
            std::unique_ptr<Event> event = std::move(ev_storer::events.front());
            ev_storer::events.pop_front();
            event->execute();
        }
    }
}