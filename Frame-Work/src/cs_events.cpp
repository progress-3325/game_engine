#include "cs_events.h"
#include "cs_logging.h"
#include <deque>
#include <memory>
#include <unordered_map>
#include <array>

namespace cs
{
    Event::~Event() = default;
    namespace detail
    {
        struct ev_storer
        {
            static std::deque<std::shared_ptr<Event>> events;
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
        EventDispatcher::dispatch(std::move(this));
    }

    void EventDispatcher::process()
    {
        Guard lock(m_lock);
        
        for (const std::shared_ptr<Event>& event : detail::ev_storer::events)
        {
            EventType ev_type(event->type());
            if (ev_type.category == static_cast<uint16_t>(EventType::EventCategories::Application))
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
        return !(Input::isKeyPressed<key>());
    }








    template<Input::Keys key>
    uint32_t key_held_count{0};

    void EventDispatcher::process()
    {
        using namespace detail;

        uint64_t i;
        while (i < 36)
        {
            key_pressed::is_pressed[i] = false;
            key_pressed::is_held[i++] = false;
        }

        while (!ev_storer::events.empty())
        {
            auto& event = ev_storer::events.front();
            EventType type = event->type();

            switch (type.category)
            {
                case 0:
                {
                    switch (type.type)
                    {

                    }
                }
                case 1:
                {
                    switch (type.type)
                    {
                        case 1:
                        {
                            
                        }

                        default: continue;
                    }
                }
                case 2:
                {
                    switch (type.type)
                    {
                        
                    }
                }
                case 3:
                {
                    switch (type.type)
                    {
                        
                    }
                }
                case 4:
                {
                    switch (type.type)
                    {
                        
                    }
                }
                case 5: continue;
                    
                default: continue;
            }
            ev_storer::events.pop_front();
        }
    }
}