#pragma once

#include "../PieceHandler.h"

class KingHandler : public PieceHandler
{
protected:
    void _get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const override;
    void _move(Position &pos, Move m) const override;

private:
    void check_castle(const Position &pos, vec2 current, Direction direction, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const;
};
