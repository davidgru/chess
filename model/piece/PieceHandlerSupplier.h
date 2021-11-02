#pragma once

#include "PieceHandler.h"

class PieceHandlerSupplier
{
public:
    static const PieceHandler &get(PieceType piece_type);

private:
    PieceHandlerSupplier() = default;
};
