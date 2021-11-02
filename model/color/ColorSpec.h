#pragma once

#include <cstdint>

#include "Color.h"

struct ColorSpec {
    const Color color;
    const Color opposite;
    const int back_row;
    const int pawn_starting_row;
    const int pawn_row_step;
    const int en_passent_row;
};
