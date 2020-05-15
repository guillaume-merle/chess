#pragma once

namespace board
{
    /* The Color enum represent a side. */
    enum Color
    {
        WHITE = 0,
        BLACK
    };

    inline Color opposite_color(Color color)
    {
        if (color == WHITE)
            return BLACK;
        return WHITE;
    }

} // namespace board
