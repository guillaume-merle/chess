#pragma once

#include <vector>

#include "bitboard.hh"
#include "move.hh"

namespace board
{
    class King
    {
    public:
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard);
    };
}
