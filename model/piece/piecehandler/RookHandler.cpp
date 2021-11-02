
#include "Rookhandler.h"

#include "../../position/Position.h"

void RookHandler::_get_legal_moves(const Position& pos, vec2 current, std::vector<vec2>& out_legal_destinations, bool /*check_king_exposure*/) const
{
    if (pos.get(current).type != PieceType::ROOK)
        std::cerr << "RookHandler called illegally!\n";

    this->scan_direction(pos, current, { 1, 0 }, out_legal_destinations);
    this->scan_direction(pos, current, { 0, 1 }, out_legal_destinations);
    this->scan_direction(pos, current, { -1, 0 }, out_legal_destinations);
    this->scan_direction(pos, current, { 0, -1 }, out_legal_destinations);
}

void RookHandler::_move(Position& pos, Move m) const
{
    Color color = pos.get(m.from).color;

    const ColorSpec& csp = ColorSpecSupplier::get(color);
    int back_row = csp.back_row;

    auto check_castling_rights = [&](int rook_column, Direction direction) {
        if (m.from == vec2{ back_row, rook_column })
            pos.get_castling_rights(color).remove_right(direction);
    };

    check_castling_rights(0, Direction::LEFT);
    check_castling_rights(7, Direction::RIGHT);
}
