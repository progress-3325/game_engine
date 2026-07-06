#include "cs_events.h"
#include "cs_logging.h"
#include <deque>
#include <memory>
#include <unordered_map>
#include <array>
#include "cs_time.h"

#define statcast_uint16(val) static_cast<uint16_t>(val)
#define statcast_uint32(val) static_cast<uint32_t>(val)
#define stcst_enum(val) statcast_uint32(val)

namespace cs
{
    Event::~Event() = default;
    namespace detail
    {
        struct ev_storer
        {
            static std::deque<std::unique_ptr<Event>> events;
        };
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

    void EventDispatcher::process()
    {
        Guard lock(m_lock);
        
        for (const std::unique_ptr<Event>& event : detail::ev_storer::events)
        {
            EventType ev_type(event->type());
            if (ev_type.category == statcast_uint16(EventType::EventCategories::Application))
            {
                if (ev_type.type == static_cast<uint32_t>(EventType::ApplicationEventType::ApplicationCloseEvent))
                {
                    
                }
            }
        }
    }

    namespace detail
    {
        struct key_pressed
        {
            static std::array<bool, 36> is_pressed;
            static std::array<bool, 36> is_held;
            static std::array<bool, 36> is_released;
            static std::array<Time::stopwatch, 36> heldTime;
        };

    }


    template<Input::Keys key>
    bool Input::isKeyPressed()
    {
        return detail::key_pressed::is_pressed[static_cast<size_t>(key)];
    }

    template<Input::Keys key>
    bool Input::isKeyHeld()
    {
        return detail::key_pressed::is_held[static_cast<size_t>(key)];
    }

    template<Input::Keys key>
    bool Input::isKeyReleased()
    {
        return detail::key_pressed::is_released[static_cast<size_t>(key)];
    }

    template<Input::Keys key>
    double Input::keyHeldTime()
    {
        return detail::key_pressed::heldTime[statcast_uint16(key)].readMilliseconds();
    }


    void KeyPressedEvent::execute() const
    {
        const auto index = statcast_uint16(this->key);

        detail::key_pressed::is_pressed[index] = true;
        detail::key_pressed::is_held[index] = true;
        detail::key_pressed::is_released[index] = false;
        detail::key_pressed::heldTime[index].start();
    }


    void EventDispatcher::process()
    {
        using namespace detail;

        key_pressed::is_pressed.fill(false);
        key_pressed::is_released.fill(false);

        while (!ev_storer::events.empty())
        {
            auto& event = ev_storer::events.front();
            ev_storer::events.pop_front();
            event->execute();

            /*EventType type = event->type();
            switch (type.category)
            {
                case stcst_enum(EventType::EventCategories::Application):
                {
                    switch (type.type)
                    {

                    }
                    break;
                }
                case stcst_enum(EventType::EventCategories::Input): // Input event type
                {
                    switch (type.type)
                    {
                        case 1: // Key pressed event type
                        {
                            auto* key_pressed_event = static_cast<KeyPressedEvent*>(event.get());

                            if (key_pressed_event)
                            {
                                Input::Keys pressed_key = key_pressed_event->key;
                                const auto index = statcast_uint16(pressed_key);
                                key_pressed::is_pressed[index] = true;
                                key_pressed::is_held[index] = true;
                                key_pressed::is_released[index] = false;
                            }
                            break;
                        }

                        case 2: // Key released event type
                        {
                            auto* key_released_event = static_cast<KeyReleasedEvent*>(event.get());

                            if (key_released_event)
                            {
                                Input::Keys released_key = key_released_event->key;
                                const auto index = statcast_uint16(released_key);
                                key_pressed::is_held[index] = false;
                                key_pressed::is_released[index] = true;
                            }
                            break;
                        }

                        default: break;
                    }
                    break;
                }
                case 2:
                {
                    switch (type.type)
                    {
                        
                    }
                    break;
                }
                case 3:
                {
                    switch (type.type)
                    {
                        
                    }
                    break;
                }
                case 4:
                {
                    switch (type.type)
                    {
                        
                    }
                    break;
                }
                case 5: continue;
                    
                default: continue;
            } */
        }
    }
}