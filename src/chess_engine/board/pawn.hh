#pragma once

#include <vector>

#include "bitboard.hh"
#include "color.hh"
#include "move.hh"
#include "chessboard.hh"

namespace board
{
    const Bitboard white_pawn_start = 1 << 15;
    const Bitboard black_pawn_start = 1ULL << 48;

    class Pawn
    {
    public:
        static Bitboard single_push(Bitboard bitboard, Color color);
        static Bitboard double_push(Bitboard bitboard, Color color);
        static Bitboard left_attack(Bitboard bitboard, Color color);
        static Bitboard right_attack(Bitboard bitboard, Color color);

        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                       Color color);
        static std::vector<Move>
        generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                       Color color, Chessboard& board);
    };
}
