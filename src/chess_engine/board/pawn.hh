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

    inline Bitboard single_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 1);

        return south(bitboard, 1);
    }

    inline Bitboard double_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 2);

        return south(bitboard, 2);
    }

    inline Bitboard left_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northwest(bitboard, 1);

        return southeast(bitboard, 1);
    }

    inline Bitboard right_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northeast(bitboard, 1);

        return southwest(bitboard, 1);
    }
} // namespace board
