
#include "BishopHandler.h"

#include "../../position/Position.h"

void BishopHandler::_get_legal_moves(const Position &pos, vec2 current, std::vector<vec2> &out_legal_destinations, bool /*check_king_exposure*/) const
{
    this->scan_direction(pos, current, {1, 1}, out_legal_destinations);
    this->scan_direction(pos, current, {1, -1}, out_legal_destinations);
    this->scan_direction(pos, current, {-1, -1}, out_legal_destinations);
    this->scan_direction(pos, current, {-1, 1}, out_legal_destinations);
}
