#include "cs_events.h"
#include "cs_logging.h"
#include <deque>
#include <memory>

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
        EventDispatcher::dispatch(std::move(this));
    }
}