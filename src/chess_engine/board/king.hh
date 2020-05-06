#pragma once

#include <vector>

#include "bitboard.hh"
#include "move.hh"

namespace board
{
    const Bitboard left_side = 0xFEFEFEFEFEFEFEFE;
    const Bitboard right_side = 0x7F7F7F7F7F7F7F7F;

    class King
    {
    public:
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard);
    };
}
