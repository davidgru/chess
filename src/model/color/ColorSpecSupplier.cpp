
#include "ColorSpecSupplier.h"

#include "../board/Chessboard.h"

/* static */ const ColorSpec& ColorSpecSupplier::get(Color color)
{
    static const ColorSpec ncs{
        Color::NONE,
        Color::NONE,
        -1,
        -1,
        0,
        -1
    };

    static const ColorSpec wcs{
        Color::WHITE,
        Color::BLACK,
        0,
        1,
        1,
        Chessboard::Height() - 3
    };

    static const ColorSpec bcs{
        Color::BLACK,
        Color::WHITE,
        Chessboard::Height() - 1,
        Chessboard::Height() - 2,
        -1,
        2
    };

    switch (color) {
        case Color::WHITE:
            return wcs;
        case Color::BLACK:
            return bcs;
        default:
            return ncs;
    }

}