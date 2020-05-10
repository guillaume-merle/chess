#pragma once

#include "magic.hh"
#include "color.hh"

namespace board
{
    namespace attacks
    {
        extern Bitboard _knight_attacks[64];
        extern Bitboard _king_attacks[64];
        extern Bitboard _pawn_attacks[2][64];

        void init_knight_attacks();

        void init_king_attacks();

        void init_pawn_attacks();

        Bitboard get_bishop_attacks(const unsigned int square,
                                    const Bitboard occupancy);

        Bitboard get_rook_attacks(const unsigned int square,
                                  const Bitboard occupancy);

        Bitboard get_queen_attacks(const unsigned int square,
                                   const Bitboard occupancy);

        Bitboard get_knight_attacks(const unsigned int square);

        Bitboard get_king_attacks(const unsigned int square);

        Bitboard get_pawn_attacks(const unsigned int square, Color color);
    }
}
