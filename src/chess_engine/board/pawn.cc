#include <iostream>

#include "pawn.hh"

namespace board
{
    Bitboard Pawn::single_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 1);

        return south(bitboard, 1);
    }

    Bitboard Pawn::double_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 2);

        return south(bitboard, 2);
    }

    Bitboard Pawn::left_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northwest(bitboard, 1);

        return southeast(bitboard, 1);
    }

    Bitboard Pawn::right_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northeast(bitboard, 1);

        return southwest(bitboard, 1);
    }
}
