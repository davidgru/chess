#pragma once

#include "../PieceHandler.h"

class PawnHandler : public PieceHandler
{
protected:
    void _get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool check_king_exposure) const override;
    void _move(Position &pos, Move m) const override;

private:
    void get_forward_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const;
    void get_capture_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const;
    void get_en_passent_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations) const;
};
