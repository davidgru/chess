
#include "NullHandler.h"

void NullHandler::_get_legal_moves(const Position & /*pos*/, vec2 /*current*/, std::vector<vec2> &out_legal_destinations, bool /*check_king_exposure*/) const
{
    out_legal_destinations.clear();
}
