
#include "StraightMovingPieceHandler.h"

#include "../../position/Position.h"

void StraightMovingPieceHandler::scan_direction(const Position& pos, vec2 current, vec2 step, std::vector<vec2>& out_legal_destinations) const
{
    PieceDesc pd = pos.get(current);
    const ColorSpec& csp = ColorSpecSupplier::get(pd.color);

    // Move in the direction until moving out of bounds or encountering another piece.
    current += step;
    while (Chessboard::in_bounds(current) && pos.get(current).type == PieceType::NULLP) {
        out_legal_destinations.push_back(current);
        current += step;
    }
    // Is there another piece that can be taken?
    if (Chessboard::in_bounds(current) && pos.get(current).color == csp.opposite)
        out_legal_destinations.push_back(current);
}
