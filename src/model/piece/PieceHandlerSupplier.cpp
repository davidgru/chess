
#include "PieceHandlerSupplier.h"

#include "piecehandler/BishopHandler.h"
#include "piecehandler/KingHandler.h"
#include "piecehandler/KnightHandler.h"
#include "piecehandler/PawnHandler.h"
#include "piecehandler/QueenHandler.h"
#include "piecehandler/RookHandler.h"

const PieceHandler &PieceHandlerSupplier::get(PieceType piece_type)
{
    static const PieceHandler h0; // just a null-object
    static const PawnHandler h1;
    static const KnightHandler h2;
    static const BishopHandler h3;
    static const RookHandler h4;
    static const QueenHandler h5;
    static const KingHandler h6;

    switch (piece_type)
    {
    case PieceType::PAWN:
        return h1;
    case PieceType::KNIGHT:
        return h2;
    case PieceType::BISHOP:
        return h3;
    case PieceType::ROOK:
        return h4;
    case PieceType::QUEEN:
        return h5;
    case PieceType::KING:
        return h6;
    default:
        return h0;
    }
}
