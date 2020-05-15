#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"
#include "chessboard.hh"

namespace board
{
    inline Bitboard northwestwest(Bitboard bitboard)
    {
        return northwest(west(bitboard, 1), 1);
    }

    inline Bitboard northeasteast(Bitboard bitboard)
    {
        return northeast(east(bitboard, 1), 1);
    }

    inline Bitboard northnorthwest(Bitboard bitboard)
    {
        return northwest(north(bitboard, 1), 1);
    }

    inline Bitboard northnortheast(Bitboard bitboard)
    {
        return northeast(north(bitboard, 1), 1);
    }

    inline Bitboard southwestwest(Bitboard bitboard)
    {
        return southwest(west(bitboard, 1), 1);
    }

    inline Bitboard southeasteast(Bitboard bitboard)
    {
        return southeast(east(bitboard, 1), 1);
    }

    inline Bitboard southsouthwest(Bitboard bitboard)
    {
        return southwest(south(bitboard, 1), 1);
    }

    inline Bitboard southsoutheast(Bitboard bitboard)
    {
        return southeast(south(bitboard, 1), 1);
    }
} // namespace board
