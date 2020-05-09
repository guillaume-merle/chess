#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"

namespace board
{
    class Bishop
    {
    public:
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard);

        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                       Chessboard& board, Color color = Color::WHITE);
    };
}
