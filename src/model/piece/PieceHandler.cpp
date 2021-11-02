
#include "PieceHandler.h"

#include "../position/Position.h"

#include "PieceHandlerSupplier.h"

#include <algorithm>

void PieceHandler::get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const
{
    out_legal_destinations.clear();

    PieceDesc pd = pos.get(current);

    this->_get_legal_moves(pos, current, out_legal_destinations, check_king_exposure);

    if (!check_king_exposure)
        return;

    auto exposes_king = [&](const vec2 &dst)
    {
        // Simulate every move. (expensive but simple)
        Position tmp = pos;
        const PieceHandler &piece_handler = PieceHandlerSupplier::get(pd.type);
        piece_handler.move(tmp, {current, dst});
        return tmp.king_exposed();
        return false;
    };

    auto new_end = std::remove_if(
        out_legal_destinations.begin(),
        out_legal_destinations.end(),
        exposes_king);
    out_legal_destinations.resize(std::distance(out_legal_destinations.begin(), new_end));
}

void PieceHandler::move(Position &pos, Move m) const
{
    if (pos.get_active_color() != pos.get(m.from).color)
        return;

    // Will the opposite color lose castling rights because a rook is taken?
    PieceDesc moved = pos.get(m.from);
    PieceDesc taken = pos.get(m.to);
    const ColorSpec &csp = ColorSpecSupplier::get(moved.color);
    const ColorSpec &taken_csp = ColorSpecSupplier::get(taken.color);

    auto check_rook = [&](int column, Direction direction)
    {
        if (m.to == vec2{taken_csp.back_row, column} && taken == PieceDesc{PieceType::ROOK, csp.opposite})
            pos.get_castling_rights(csp.color).remove_right(direction);
    };

    check_rook(0, Direction::LEFT);
    check_rook(7, Direction::RIGHT);

    // Call custom function.
    this->_move(pos, m);

    // Execute move.
    PieceDesc pd = pos.take(m.from);
    pos.place(pd, m.to);
}

void PieceHandler::_get_legal_moves(const class Position & /*pos*/, vec2 /*current*/, std::vector<vec2> &out_legal_destinations, bool /*check_king_exposure*/) const
{
    out_legal_destinations.clear();
}

void PieceHandler::_move(class Position & /*pos*/, Move /*m*/) const
{
    // Empty default.
}
