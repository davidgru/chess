#pragma once

#include "StraightMovingPieceHandler.h"

class QueenHandler : public StraightMovingPieceHandler
{
protected:
    void _get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const override;
};
