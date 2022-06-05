#pragma once

#include "PieceTextures.h"

#include "../../model/ChessState.h"

#include <string>
#include <string_view>

#include <algorithm>

class Screenbuffer
{
public:
    Screenbuffer();

    void redraw(const ChessState &state,
                const std::vector<std::pair<std::string, std::string>> &command_descs);
    std::string_view get_frame() const;

private:
    void reset();

    void draw_chess_pattern();

    void draw_pieces(const ChessState &state);
    void draw_legal_moves(const ChessState &state);
    void draw_game_info(
        const ChessState &state,
        const std::vector<std::pair<std::string, std::string>> &command_descs);

    static std::string construct_game_info(
        const ChessState &state,
        const std::vector<std::pair<std::string, std::string>> &command_descs);

    char &get(int y, int x);

private:
    static const int BOARD_HEIGHT =
        PieceTextures::TEXTURE_HEIGHT * Chessboard::Height();
    static const int BOARD_WIDTH =
        PieceTextures::TEXTURE_WIDTH * Chessboard::Width();

    static const int BOARD_HEIGHT_OFFSET = 0;
    static const int BOARD_WIDTH_OFFSET = 0;

    static const int ROW_INDICES_HEIGHT_OFFSET = BOARD_HEIGHT_OFFSET;
    static const int ROW_INDICES_WIDTH_OFFSET = BOARD_WIDTH_OFFSET + BOARD_WIDTH;

    static const int ROW_INDICES_HEIGHT = BOARD_HEIGHT;
    static const int ROW_INDICES_WIDTH = PieceTextures::TEXTURE_WIDTH;

    static const int COLUMN_INDICES_HEIGHT_OFFSET =
        BOARD_HEIGHT_OFFSET + BOARD_HEIGHT;
    static const int COLUMN_INDICES_WIDTH_OFFSET = BOARD_WIDTH_OFFSET;

    static const int COLUMN_INDICES_HEIGHT = PieceTextures::TEXTURE_HEIGHT;
    static const int COLUMN_INDICES_WIDTH = BOARD_WIDTH;

    static const int MESSAGE_BOARD_HEIGHT = BOARD_HEIGHT;
    static const int MESSAGE_BOARD_WIDTH = 80;

    static const int MESSAGE_BOARD_HEIGHT_OFFSET = BOARD_HEIGHT_OFFSET;
    static const int MESSAGE_BOARD_WIDTH_OFFSET =
        ROW_INDICES_WIDTH_OFFSET + ROW_INDICES_WIDTH;

    static const int SCREEN_HEIGHT =
        BOARD_HEIGHT_OFFSET +
        std::max(BOARD_HEIGHT + COLUMN_INDICES_HEIGHT, MESSAGE_BOARD_HEIGHT);
    static const int SCREEN_WIDTH = BOARD_WIDTH_OFFSET + BOARD_WIDTH +
                                    ROW_INDICES_WIDTH + MESSAGE_BOARD_WIDTH + 1;

    static const char LIGHT_SQUARE_COLOR = ':';
    static const char DARK_SQUARE_COLOR = '.';
    static const char LIGHT_PIECE_COLOR = '#';
    static const char DARK_PIECE_COLOR = ' ';
    static const char LEGAL_MOVE_COLOR = '*';

    std::string screenbuffer;
};
