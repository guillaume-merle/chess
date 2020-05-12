#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"
#include "chessboard.hh"

namespace board
{
    class Knight
    {
    public:
        static Bitboard northwestwest(Bitboard bitboard);
        static Bitboard northeasteast(Bitboard bitboard);
        static Bitboard southwestwest(Bitboard bitboard);
        static Bitboard southeasteast(Bitboard bitboard);
        static Bitboard northnorthwest(Bitboard bitboard);
        static Bitboard northnortheast(Bitboard bitboard);
        static Bitboard southsouthwest(Bitboard bitboard);
        static Bitboard southsoutheast(Bitboard bitboard);
    };
}
