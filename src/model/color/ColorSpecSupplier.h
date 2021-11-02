#pragma once

#include "ColorSpec.h"

class ColorSpecSupplier
{
public:
    static const ColorSpec &get(Color color);

private:
    ColorSpecSupplier() = default;
};
