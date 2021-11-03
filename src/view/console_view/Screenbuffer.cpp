
#include "Screenbuffer.h"

#include <cstring>

#include "../../model/GameState.h"
#include "../../model/piece/PieceDesc.h"

// enum -> string mappings

static const std::string &game_state_to_string(GameState gamestate)
{
    static const std::string t[] = {
        "IN_PROGRESS",
        "WHITE_WON",
        "BLACK_WON",
        "DRAW",
    };
    return t[static_cast<size_t>(gamestate)];
}

static const std::string &color_to_string(Color color)
{
    static const std::string t[] = {
        "NONE",
        "WHITE",
        "BLACK"};
    return t[static_cast<size_t>(color)];
}

Screenbuffer::Screenbuffer()
{
    this->screenbuffer.resize(SCREEN_HEIGHT * SCREEN_WIDTH);
    this->reset();
}

void Screenbuffer::redraw(const ChessState &state, const std::vector<std::pair<std::string, std::string>> &command_descs)
{
    this->reset();
    this->draw_chess_pattern();
    this->draw_pieces(state);
    this->draw_legal_moves(state);
    this->draw_game_info(state, command_descs);
}

char &Screenbuffer::get(int y, int x)
{
    return this->screenbuffer[y * SCREEN_WIDTH + x];
}

std::string_view Screenbuffer::get_frame() const
{
    return &this->screenbuffer[0];
}

void Screenbuffer::reset()
{
    std::fill(this->screenbuffer.begin(), this->screenbuffer.end(), ' ');
    for (int i = 0; i < SCREEN_HEIGHT; i++)
        this->get(i, SCREEN_WIDTH - 1) = '\n';

    const auto th = PieceTextures::TEXTURE_HEIGHT;
    const auto tw = PieceTextures::TEXTURE_WIDTH;

    // draw row indices
    for (int i = 0; i < Chessboard::Height(); i++)
    {
        int midr = ROW_INDICES_HEIGHT_OFFSET + i * th + th / 2;
        int midc = ROW_INDICES_WIDTH_OFFSET + ROW_INDICES_WIDTH / 2;
        this->get(midr, midc) = static_cast<char>((Chessboard::Height() - i - 1) + '1'); // convert to ascii number
    }
    // draw column indices
    for (int j = 0; j < Chessboard::Width(); j++)
    {
        int midr = COLUMN_INDICES_HEIGHT_OFFSET + COLUMN_INDICES_HEIGHT / 2;
        int midc = COLUMN_INDICES_WIDTH_OFFSET + j * tw + tw / 2;
        this->get(midr, midc) = static_cast<char>(j + 'a'); // convert to ascii letter
    }
}

void Screenbuffer::draw_chess_pattern()
{
    const int th = PieceTextures::TEXTURE_HEIGHT;
    const int tw = PieceTextures::TEXTURE_WIDTH;

    for (int i = 0; i < Chessboard::Height(); i++)
    {
        for (int j = 0; j < Chessboard::Width(); j++)
        {
            char fill = (i + j) % 2 == 0 ? DARK_SQUARE_COLOR : LIGHT_SQUARE_COLOR;

            for (int k = 0; k < th; k++)
            {
                int y = BOARD_HEIGHT_OFFSET + (Chessboard::Height() - i - 1) * th + k;
                int x = BOARD_WIDTH_OFFSET + j * tw;
                memset(&this->get(y, x), fill, tw);
            }
        }
    }
}

void Screenbuffer::draw_pieces(const ChessState &state)
{
    const int th = PieceTextures::TEXTURE_HEIGHT;
    const int tw = PieceTextures::TEXTURE_WIDTH;

    for (int i = 0; i < Chessboard::Height(); i++)
    {
        for (int j = 0; j < Chessboard::Width(); j++)
        {
            PieceDesc pd = state.position.get({i, j});
            const char *texture = PieceTextures::get_texture(pd.type);
            for (int k = 0; k < th; k++)
            {
                for (int l = 0; l < tw; l++)
                {
                    if (texture[k * tw + l] == '#')
                    {
                        char fill = pd.color == Color::WHITE ? LIGHT_PIECE_COLOR : DARK_PIECE_COLOR;

                        int y = BOARD_HEIGHT_OFFSET + (Chessboard::Height() - i - 1) * th + k;
                        int x = BOARD_WIDTH_OFFSET + j * tw + l;
                        this->get(y, x) = fill;
                    }
                }
            }
        }
    }
}

void Screenbuffer::draw_legal_moves(const ChessState &state)
{
    const int th = PieceTextures::TEXTURE_HEIGHT;
    const int tw = PieceTextures::TEXTURE_WIDTH;

    for (vec2 dst : state.legal_moves)
    {
        int i = dst.r;
        int j = dst.c;

        int y = BOARD_HEIGHT_OFFSET + (Chessboard::Width() - i - 1) * th + th / 2;
        int x = BOARD_WIDTH_OFFSET + j * tw + tw / 2;
        this->get(y, x) = LEGAL_MOVE_COLOR;
    }
}

void Screenbuffer::draw_game_info(const ChessState &state, const std::vector<std::pair<std::string, std::string>> &command_descs)
{
    const auto game_info = Screenbuffer::construct_game_info(state, command_descs);

    auto display_line = [this, row = 0](auto begin, auto end) mutable
    {
        auto it = this->screenbuffer.begin();
        it += MESSAGE_BOARD_HEIGHT_OFFSET * SCREEN_WIDTH;
        it += MESSAGE_BOARD_WIDTH_OFFSET;
        it += row * SCREEN_WIDTH;
        std::copy(begin, end, it);
        row++;
    };

    auto begin = game_info.begin();
    auto end = std::find(begin, game_info.end(), '\n');
    while (end != game_info.end())
    {
        display_line(begin, end);
        begin = end + 1;
        end = std::find(begin, game_info.end(), '\n');
    }
    display_line(begin, end);
}

/*static*/ std::string Screenbuffer::construct_game_info(const ChessState &state, const std::vector<std::pair<std::string, std::string>> &command_descs)
{
    std::string game_info;
    game_info += "Gamestate:    " + game_state_to_string(state.game_state) + "\n";
    game_info += "Active color: " + color_to_string(state.position.get_active_color()) + "\n";
    game_info += "\n";
    game_info += "Commands: \n";
    game_info += "\n";
    for (const auto &[name, description] : command_descs)
    {
        game_info += "Name: " + name + "\n";
        game_info += description + "\n";
        game_info += "\n";
    }
    return game_info;
}
