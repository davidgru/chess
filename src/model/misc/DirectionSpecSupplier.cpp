
#include "DirectionSpecSupplier.h"

/* static */ const DirectionSpec &DirectionSpecSupplier::get(Direction direction)
{

    static const DirectionSpec null{
        -1,
        -1,
        -1};

    static const DirectionSpec left{
        0,
        2,
        3,
    };

    static const DirectionSpec right{
        7,
        6,
        5};

    switch (direction)
    {
    case Direction::LEFT:
        return left;
    case Direction::RIGHT:
        return right;
    default:
        throw "nulldsp";
        return null;
    }
}
