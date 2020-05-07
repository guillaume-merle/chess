#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"

namespace board
{
    class Knight
    {
    public:
        static Bitboard northwestwest(Bitboard bitboard, Color color);
        static Bitboard northeasteast(Bitboard bitboard, Color color);
        static Bitboard southwestwest(Bitboard bitboard, Color color);
        static Bitboard southeasteast(Bitboard bitboard, Color color);
        static Bitboard northnorthwest(Bitboard bitboard, Color color);
        static Bitboard northnortheast(Bitboard bitboard, Color color);
        static Bitboard southsouthwest(Bitboard bitboard, Color color);
        static Bitboard southsoutheast(Bitboard bitboard, Color color);

        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                       Color color);
    };
}
