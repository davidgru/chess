#pragma once

#include <list>
#include <unordered_map>

#include "events/EventPublisher.h"
#include "ChessState.h"

class Chess : public EventPublisher<ChessState>
{
public:
    Chess();

    // Invokes callback.
    void request_update();

    // Returns true if the selected square is not occupied by a piece of the active player.
    bool select(vec2 v);

    // Returns true if the move is illegal.
    bool move(vec2 v);

private:
    // Update after a move was made.
    void update_game_status();

    void place_pieces();

private:
    ChessState state;

    // Used to detect 3-fold repetition.
    std::unordered_map<Position, int> all_positions;
};
