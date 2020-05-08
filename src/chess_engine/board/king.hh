#pragma once

#include <vector>

#include "bitboard.hh"
#include "move.hh"
#include "color.hh"
#include "chessboard.hh"

namespace board
{
    class King
    {
    public:
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard);

        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                       Chessboard& board, Color color = Color::WHITE);
    };
}
