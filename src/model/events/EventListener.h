#pragma once

#include "../ChessState.h"

template <class State>
class EventListener
{
public:
    virtual void on_update(const State &state) = 0;
};
