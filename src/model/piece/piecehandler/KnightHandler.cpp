
#include "Knighthandler.h"

#include "../../position/Position.h"

void KnightHandler::_get_legal_moves(const Position& pos, vec2 current, std::vector<vec2>& out_legal_destinations, bool /*check_king_exposure*/) const
{
    out_legal_destinations.clear();

    vec2 dsts[] = {
        current + vec2{2, 1},
        current + vec2{1, 2},
        current + vec2{-1, 2},
        current + vec2{-2, 1},
        current + vec2{-2, -1},
        current + vec2{-1, -2},
        current + vec2{1, -2},
        current + vec2{2, -1},
    };

    for (auto dst : dsts)     {
        if (Chessboard::in_bounds(dst) && pos.get(dst).color != pos.get(current).color)
            out_legal_destinations.emplace_back(dst);
    }
}
