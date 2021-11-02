#pragma once

#include <functional>

#include "../misc/Direction.h"

class CastlingRights
{
public:
    CastlingRights();

    bool has_right(Direction direction) const;
    void remove_right(Direction direction);

    bool operator==(const CastlingRights &other) const;

private:
    bool left : 1, right : 1;

    friend std::hash<CastlingRights>;
};

namespace std
{
    template <>
    struct hash<CastlingRights>
    {
        size_t operator()(const CastlingRights &cr) const;
    };
} // namespace std
