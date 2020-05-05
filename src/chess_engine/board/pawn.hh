#pragma once

#include "bitboard.hh"
#include "color.hh"

namespace board
{
    class Pawn
    {
        static Bitboard single_push(Bitboard bitboard, Color color);
        static Bitboard double_push(Bitboard bitboard, Color color);
        static Bitboard left_attack(Bitboard bitboard, Color color);
        static Bitboard right_attack(Bitboard bitboard, Color color);
    };
}
