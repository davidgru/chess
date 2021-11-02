
#include "Chess.h"

#include <algorithm>

#include "board/Chessboard.h"
#include "piece/PieceHandlerSupplier.h"
#include "position/Position.h"

Chess::Chess()
{
    this->state.game_state = GameState::IN_PROGRESS;
    this->state.selected = { -1, -1 };
    this->place_pieces();
}

void Chess::request_update()
{
    this->notify_all(this->state);
}

bool Chess::select(vec2 v)
{
    if (this->state.game_state != GameState::IN_PROGRESS)
        return true;
    if (!Chessboard::in_bounds(v))
        return true;

    this->state.selected = v;
    this->state.position.get_legal_moves(v, this->state.legal_moves);

    this->notify_all(this->state);
    return false;
}

bool Chess::move(vec2 v)
{
    if (this->state.game_state != GameState::IN_PROGRESS)
        return true;
    if (!Chessboard::in_bounds(v))
        return true;

    // Is the move legal?
    auto it = std::find(this->state.legal_moves.begin(), this->state.legal_moves.end(), v);
    if (it == this->state.legal_moves.end())
        return true;

    // Move
    if (this->state.position.move({ this->state.selected, v }))
        return true;

    // Prepare for next move
    this->state.selected = { -1, -1 };
    this->state.legal_moves.clear();

    // 3-fold repetition?
    this->all_positions[this->state.position]++;

    this->update_game_status();

    this->notify_all(this->state);
    return false;
}

void Chess::update_game_status()
{
    // 3-fold repetition?
    if (this->all_positions[this->state.position] >= 3) {
        this->state.game_state = GameState::DRAW;
        return;
    }
    // player able to move?
    bool has_moves = this->state.position.can_move_at_all();
    if (has_moves) {
        this->state.game_state = GameState::IN_PROGRESS;
        return;
    }

    // check- or stale-mate?
    bool king_exposed = this->state.position.king_exposed();
    if (king_exposed)
        this->state.game_state = this->state.position.get_active_color() == Color::WHITE ? GameState::BLACK_WON : GameState::WHITE_WON;
    else
        this->state.game_state = GameState::DRAW;
}

void Chess::place_pieces()
{
    this->state.position.place({ PieceType::ROOK, Color::WHITE }, { 0, 0 });
    // this->state.position.place({ PieceType::KNIGHT, Color::WHITE }, { 0, 1 });
    // this->state.position.place({ PieceType::BISHOP, Color::WHITE }, { 0, 2 });
    // this->state.position.place({ PieceType::QUEEN, Color::WHITE }, { 0, 3 });
    this->state.position.place({ PieceType::KING, Color::WHITE }, { 0, 4 });
    // this->state.position.place({ PieceType::BISHOP, Color::WHITE }, { 0, 5 });
    // this->state.position.place({ PieceType::KNIGHT, Color::WHITE }, { 0, 6 });
    this->state.position.place({ PieceType::ROOK, Color::WHITE }, { 0, 7 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 0 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 1 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 2 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 3 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 4 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 5 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 6 });
    // this->state.position.place({ PieceType::PAWN, Color::WHITE }, { 1, 7 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 0 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 1 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 2 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 3 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 4 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 5 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 6 });
    // this->state.position.place({ PieceType::PAWN, Color::BLACK }, { 6, 7 });
    this->state.position.place({ PieceType::ROOK, Color::BLACK }, { 7, 0 });
    // this->state.position.place({ PieceType::KNIGHT, Color::BLACK }, { 7, 1 });
    // this->state.position.place({ PieceType::BISHOP, Color::BLACK }, { 7, 2 });
    // this->state.position.place({ PieceType::QUEEN, Color::BLACK }, { 7, 3 });
    this->state.position.place({ PieceType::KING, Color::BLACK }, { 7, 4 });
    // this->state.position.place({ PieceType::BISHOP, Color::BLACK }, { 7, 5 });
    // this->state.position.place({ PieceType::KNIGHT, Color::BLACK }, { 7, 6 });
    this->state.position.place({ PieceType::ROOK, Color::BLACK }, { 7, 7 });
}
