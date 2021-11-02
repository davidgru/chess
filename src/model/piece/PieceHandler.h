#pragma once

#include "PieceType.h"
#include "../color/Color.h"
#include "../board/Chessboard.h"

#include <vector>

#include "../misc/Direction.h"
#include "../misc/Move.h"

#include "PieceDesc.h"

#include "../color/ColorSpecSupplier.h"

#include <exception>

class PieceHandler {
public:
    void get_legal_moves(const class Position& pos, vec2 current, std::vector<vec2>& out_legal_destinations, bool check_king_exposure = true) const;
    void move(class Position& pos, Move m) const;

protected:
    virtual void _get_legal_moves(const class Position& pos, vec2 current, std::vector<vec2>& out_legal_destinations, bool check_king_exposure) const = 0;
    virtual void _move(class Position& pos, Move m) const;
};
