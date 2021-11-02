
#include "CastlingRights.h"

CastlingRights::CastlingRights()
    : left(true), right(true)
{
}

bool CastlingRights::has_right(Direction direction) const
{
    return direction == Direction::LEFT ? this->left : this->right;
}

void CastlingRights::remove_right(Direction direction)
{
    if (direction == Direction::LEFT)
        this->left = 0;
    else if (direction == Direction::RIGHT)
        this->right = 0;
}

bool CastlingRights::operator==(const CastlingRights &other) const
{
    return this->left == other.left && this->right == other.right;
}

size_t std::hash<CastlingRights>::operator()(const CastlingRights &cr) const
{
    size_t h1 = std::hash<int>{}(cr.left);
    size_t h2 = std::hash<int>{}(cr.right);
    return (h1 << 1) ^ h2;
}
