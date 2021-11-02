
#include "KingHandler.h"

#include <algorithm>

#include "../../position/Position.h"

#include "../../misc/DirectionSpecSupplier.h"

void KingHandler::_get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const
{
    Color color = pos.get(current).color;

    vec2 dsts[] = {
        current + vec2{1, 0},
        current + vec2{1, 1},
        current + vec2{0, 1},
        current + vec2{-1, 1},
        current + vec2{-1, 0},
        current + vec2{-1, -1},
        current + vec2{0, -1},
        current + vec2{1, -1},
    };

    for (auto dst : dsts)
    {
        if (Chessboard::in_bounds(dst) && pos.get(dst).color != color)
            out_legal_destinations.emplace_back(dst);
    }

    this->check_castle(pos, current, Direction::LEFT, out_legal_destinations, check_king_exposure);
    this->check_castle(pos, current, Direction::RIGHT, out_legal_destinations, check_king_exposure);
}

void KingHandler::_move(Position &pos, Move m) const
{
    Color color = pos.get(m.from).color;

    // Castle?
    int column_step = m.to.c - m.from.c;
    if (std::abs(column_step) == 2)
    {
        // Move the rook.
        Direction castle_direction = column_step > 0 ? Direction::RIGHT : Direction::LEFT;
        const DirectionSpec &dsp = DirectionSpecSupplier::get(castle_direction);
        PieceDesc rook_pd = pos.take({m.to.r, dsp.rook_column});
        pos.place(rook_pd, {m.to.r, dsp.rook_castle_destination});
    }
    // No castling allowed anymore.
    CastlingRights &clr = pos.get_castling_rights(color);
    clr.remove_right(Direction::LEFT);
    clr.remove_right(Direction::RIGHT);
}

void KingHandler::check_castle(const Position &pos, vec2 current, Direction direction, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const
{
    const Color color = pos.get(current).color;
    const Color opposite = ColorSpecSupplier::get(color).opposite;
    const int d = static_cast<int>(direction);

    // King/Rook moved?
    if (!pos.get_castling_rights(color).has_right(direction))
        return;

    const DirectionSpec dsp = DirectionSpecSupplier::get(direction);

    // All clear between king and rook?
    for (int i = current.c + d; i != dsp.rook_column; i += d)
    {
        vec2 square = {current.r, i};
        if (pos.get(square).type != PieceType::NULLP)
            return;
    }

    // King in check or path of king controlled by opposite colored piece?
    if (check_king_exposure)
    {
        for (int i = current.c; i != (dsp.king_castle_destination + d); i += d)
        {
            vec2 square = {current.r, i};
            if (pos.controls_square(opposite, square))
                return;
        }
    }

    out_legal_destinations.emplace_back(vec2{current.r, dsp.king_castle_destination});
}
