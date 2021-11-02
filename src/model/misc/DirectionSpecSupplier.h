#pragma once

#include "Direction.h"
#include "DirectionSpec.h"

class DirectionSpecSupplier
{
public:
    static const DirectionSpec &get(Direction direction);

private:
    DirectionSpecSupplier() = default;
};