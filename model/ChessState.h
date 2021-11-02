#pragma once

#include <vector>

#include "GameState.h"
#include "misc/vec2.h"
#include "position/Position.h"

struct ChessState
{
    GameState game_state;
    Position position;
    vec2 selected;
    std::vector<vec2> legal_moves;
};
