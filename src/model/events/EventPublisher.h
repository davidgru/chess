#pragma once

#include <list>

#include "EventListener.h"

template <class State>
class EventPublisher
{
public:
    void add_event_listener(EventListener<State> *event_listener)
    {
        this->event_listeners.push_back(event_listener);
    }

    void notify_all(const State &state)
    {
        for (EventListener<State> *event_listener : this->event_listeners)
            event_listener->on_update(state);
    }

private:
    std::list<EventListener<State> *> event_listeners;
};
