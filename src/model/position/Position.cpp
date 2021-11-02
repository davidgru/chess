
#include "Position.h"

#include <algorithm>

#include "../color/ColorSpecSupplier.h"
#include "../piece/PieceHandlerSupplier.h"

Position::Position()
    : cbd({ PieceType::NULLP, Color::NONE }), active_color(Color::WHITE)
{
}

Color Position::get_active_color() const
{
    return this->active_color;
}

std::optional<std::pair<Color, int>> Position::get_en_passent() const
{
    return this->en_passent;
}

PieceDesc Position::get(vec2 square) const
{
    return this->cbd.get(square);
}

const CastlingRights& Position::get_castling_rights(Color color) const
{
    return this->castling_rights[static_cast<size_t>(color)];
}

CastlingRights& Position::get_castling_rights(Color color)
{
    return this->castling_rights[static_cast<size_t>(color)];
}

void Position::place(PieceDesc pd, vec2 square)
{
    this->cbd.place(pd, square);
}

bool Position::move(const Move& m)
{
    PieceDesc pd = this->get(m.from);

    const PieceHandler& piece_handler = PieceHandlerSupplier::get(pd.type);
    piece_handler.move(*this, m);

    this->rotate_active_color();
    return false;
}

PieceDesc Position::take(vec2 square)
{
    return this->cbd.take(square);
}

void Position::rotate_active_color()
{
    if (this->en_passent.has_value() && this->en_passent->first != this->active_color)
        this->en_passent.reset();
    const ColorSpec& csp = ColorSpecSupplier::get(this->active_color);
    this->active_color = csp.opposite;
}

void Position::get_legal_moves(vec2 square, std::vector<vec2>& out_legal_destinations) const
{
    PieceDesc pd = cbd.get(square);

    if (pd.color != this->active_color)
        return;

    const PieceHandler& piece_handler = PieceHandlerSupplier::get(pd.type);
    piece_handler.get_legal_moves(*this, square, out_legal_destinations);
}

bool Position::can_move_at_all() const
{
    std::vector<vec2> legal_moves;
    for (const auto& [pos, pd] : this->cbd) {
        this->get_legal_moves(pos, legal_moves);
        if (!legal_moves.empty())
            return true;
    }
    return false;
}

bool Position::controls_square(Color color, vec2 square) const
{
    std::vector<vec2> legal_dsts;

    auto controls_from = [&](const std::pair<vec2, PieceDesc>& pr) -> bool {
        const auto& [pos, pd] = pr;

        if (pd.color != color)
            return false;

        const PieceHandler& piece_handler = PieceHandlerSupplier::get(pd.type);
        piece_handler.get_legal_moves(*this, pos, legal_dsts, false);

        return std::find(legal_dsts.begin(), legal_dsts.end(), square) != legal_dsts.end();
        return false;
    };

    return std::any_of(this->cbd.begin(), this->cbd.end(), controls_from);
}

bool Position::king_exposed() const
{
    const ColorSpec& csp = ColorSpecSupplier::get(this->active_color);

    vec2 king_pos = this->cbd.find({ PieceType::KING, this->active_color });
    // If there is no king then the king is not exposed, right?
    return this->controls_square(csp.opposite, king_pos);
}

void Position::register_en_passent_opportunity(int column)
{
    this->en_passent = { this->active_color, column };
}

bool Position::operator==(const Position& other) const
{
    bool castling_rights_equal = true;
    for (int i = 0; i < 3; i++)
        if (this->castling_rights[i] == other.castling_rights[i])
            castling_rights_equal = false;
    return castling_rights_equal && this->cbd == other.cbd && this->active_color == other.active_color;
}

size_t std::hash<Position>::operator()(const Position& pos) const
{
    size_t h1 = std::hash<Chessboard>{}(pos.cbd);
    size_t h20 = std::hash<CastlingRights>{}(pos.castling_rights[0]);
    size_t h21 = std::hash<CastlingRights>{}(pos.castling_rights[1]);
    size_t h22 = std::hash<CastlingRights>{}(pos.castling_rights[2]);
    size_t h2 = (h20 << 2) ^ (h21 << 1) ^ h22;
    size_t h3 = std::hash<Color>{}(pos.active_color);
    return (h1 << 2) ^ (h2 << 1) ^ h3;
}
