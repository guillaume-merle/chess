#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"

namespace board
{
    class Rook
    {
    public:
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard);
    };
}
