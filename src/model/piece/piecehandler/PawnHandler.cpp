
#include "PawnHandler.h"

#include <algorithm>

#include "../../position/Position.h"

void PawnHandler::_get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool /*check_king_exposure*/) const
{
    this->get_forward_moves(pos, current, out_legal_destinations);
    this->get_capture_moves(pos, current, out_legal_destinations);
    this->get_en_passent_moves(pos, current, out_legal_destinations);
}

void PawnHandler::_move(Position &pos, Move m) const
{
    PieceDesc pd = pos.get(m.from);
    const ColorSpec &csp = ColorSpecSupplier::get(pd.color);
    const ColorSpec &opposite_csp = ColorSpecSupplier::get(csp.opposite);

    // Develop to a queen automatically.
    if (m.to.r == opposite_csp.back_row)
        pos.place(PieceDesc{PieceType::QUEEN, pd.color}, m.from);

    // vertical move, but no capture -> en passent
    if (m.from.c != m.to.c && pos.get(m.to).type == PieceType::NULLP)
        pos.take({m.from.r, m.to.c});

    // Has the opposing player the opportunity to en passent?
    int row_diff = std::abs(m.to.r - m.from.r);
    if (row_diff == 2)
        pos.register_en_passent_opportunity(m.from.c);
}

void PawnHandler::get_forward_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const
{
    const ColorSpec &csp = ColorSpecSupplier::get(pos.get(current).color);

    // Can move one step forward?
    vec2 dst = current + vec2{csp.pawn_row_step, 0};
    if (!Chessboard::in_bounds(dst) || pos.get(dst).type != PieceType::NULLP)
        return;
    out_legal_destinations.push_back(dst);
    // Can move two steps forward?
    dst += vec2{csp.pawn_row_step, 0};
    if (current.r != csp.pawn_starting_row || !Chessboard::in_bounds(dst) || pos.get(dst).type != PieceType::NULLP)
        return;
    out_legal_destinations.push_back(dst);
}

void PawnHandler::get_capture_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const
{
    const ColorSpec &csp = ColorSpecSupplier::get(pos.get(current).color);

    auto check_direction = [&](Direction direction)
    {
        vec2 dst = current + vec2{csp.pawn_row_step, static_cast<int>(direction)};
        if (Chessboard::in_bounds(dst) && pos.get(dst).color == csp.opposite)
            out_legal_destinations.push_back(dst);
    };

    check_direction(Direction::LEFT);
    check_direction(Direction::RIGHT);
}

void PawnHandler::get_en_passent_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const
{
    const ColorSpec &csp = ColorSpecSupplier::get(pos.get(current).color);

    if (auto en_passent = pos.get_en_passent())
    {
        vec2 en_passent_square = {csp.en_passent_row, en_passent->second};

        auto check_en_passent = [&](Direction direction)
        {
            vec2 capture_square = current + vec2{csp.pawn_row_step, static_cast<int>(direction)};
            if (capture_square == en_passent_square)
                out_legal_destinations.push_back(en_passent_square);
        };

        check_en_passent(Direction::LEFT);
        check_en_passent(Direction::RIGHT);
    }
}
