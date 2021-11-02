#pragma once

#include "../PieceHandler.h"

class StraightMovingPieceHandler : public PieceHandler
{
protected:
    void scan_direction(const Position &pos, vec2 current, vec2 step, std::vector<vec2> &out_legal_destinations) const;
};
