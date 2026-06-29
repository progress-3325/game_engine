#include "cs_events.h"
#include "cs_logging.h"


namespace cs
{
    void EventDispatcher::dispatch(const EventType& ev)
    {
        Guard lock(m_lock);
        logger::log("Dispatching Event!", L_CODE::C_DEBUG);

        logger::log("Event Dispatched!", L_CODE::C_DEBUG);
    }
}