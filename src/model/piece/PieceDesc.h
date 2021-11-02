#pragma once

#include <functional>
#include <cstddef>

#include "../color/Color.h"
#include "PieceType.h"

struct PieceDesc
{
    PieceType type;
    Color color;

    bool operator==(const PieceDesc &other) const
    {
        return this->type == other.type && this->color == other.color;
    }
};

namespace std
{

    template <>
    struct hash<PieceDesc>
    {
        size_t operator()(const PieceDesc &pd) const
        {
            size_t h1 = std::hash<PieceType>()(pd.type);
            size_t h2 = std::hash<Color>()(pd.color);
            return h1 ^ (h2 << 1);
        }
    };

} // namespace std
