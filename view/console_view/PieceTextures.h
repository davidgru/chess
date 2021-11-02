#pragma once

#include "../../model/piece/PieceType.h"

class PieceTextures
{
public:
    static const int TEXTURE_HEIGHT = 5;
    static const int TEXTURE_WIDTH = 11;

    // returns a pointer to the texture layed out in row-major format
    static const char *get_texture(PieceType piece_type);

private:
    PieceTextures();
};