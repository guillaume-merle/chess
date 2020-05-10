#pragma once

#include "magic.hh"

namespace board
{
    namespace attacks
    {
        extern Bitboard _knight_attacks[64];

        void init_knight_attacks();

        Bitboard get_bishop_attacks(const unsigned int square,
                                    const Bitboard occupancy);

        Bitboard get_rook_attacks(const unsigned int square,
                                  const Bitboard occupancy);

        Bitboard get_queen_attacks(const unsigned int square,
                                   const Bitboard occupancy);

        Bitboard get_knight_attacks(const unsigned int square);
    }
}
