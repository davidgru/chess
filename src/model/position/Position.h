#pragma once

#include <optional>

#include "../board/Chessboard.h"
#include "CastlingRights.h"

#include "../piece/PieceDesc.h"
#include "../color/Color.h"

#include "../misc/vec2.h"

#include "../piece/piecehandler/BishopHandler.h"

class Position
{
public:
    Position();

    Color get_active_color() const;
    PieceDesc get(vec2 square) const;
    std::optional<std::pair<Color, int>> get_en_passent() const;
    CastlingRights &get_castling_rights(Color color);
    const CastlingRights &get_castling_rights(Color color) const;

    bool move(const Move &m);

    // Gets all legal moves for the piece placed on square.
    void get_legal_moves(vec2 square, std::vector<vec2> &out_legal_destinations) const;

    // Returns true if the active player has at least one legal move.
    bool can_move_at_all() const;

    // Returns true if the king of the active color can be captured.
    bool king_exposed() const;

    // Used by the piece handlers.
    PieceDesc take(vec2 square);
    void place(PieceDesc pd, vec2 square);

    // Called by a the pawn piece handler.
    void register_en_passent_opportunity(int column);

    // Needed for unordered hashing.
    bool operator==(const Position &other) const;

    // Checks if a piece of color controls square.
    bool controls_square(Color color, vec2 square) const;

private:
    void rotate_active_color();

    Chessboard cbd;
    CastlingRights castling_rights[3];
    Color active_color;
    // Indicates that a pawn of color Color can be captured en passent in column int.
    std::optional<std::pair<Color, int>> en_passent;

    friend std::hash<Position>;
};

namespace std
{
    template <>
    struct hash<Position>
    {
        size_t operator()(const Position &pos) const;
    };
} // namespace std
