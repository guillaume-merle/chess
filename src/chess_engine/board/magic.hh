#pragma once

#include "bitboard.hh"

#define MINIMAL_B_BITS_SHIFT(square) 55
#define MINIMAL_R_BITS_SHIFT(square) 52

namespace board
{
    extern const Bitboard magicmoves_r_magics[64];
    extern const Bitboard magicmoves_r_mask[64];
    extern const Bitboard magicmoves_b_magics[64];
    extern const Bitboard magicmoves_b_mask[64];
    extern const unsigned int magicmoves_b_shift[64];
    extern const unsigned int magicmoves_r_shift[64];
    extern const Bitboard* magicmoves_b_indices[64];
    extern const Bitboard* magicmoves_r_indices[64];

    static inline Bitboard BmagicNOMASK(const unsigned int square,
                                        const Bitboard occupancy)
    {
        return *(magicmoves_b_indices[square]+(((occupancy)*magicmoves_b_magics[square])>>magicmoves_b_shift[square]));
    }

    static inline Bitboard RmagicNOMASK(const unsigned int square,
                                        const Bitboard occupancy)
    {
        return *(magicmoves_r_indices[square]+(((occupancy)*magicmoves_r_magics[square])>>magicmoves_r_shift[square]));
    }

    static inline Bitboard QmagicNOMASK(const unsigned int square,
                                        const Bitboard occupancy)
    {
        return BmagicNOMASK(square,occupancy)
               | RmagicNOMASK(square,occupancy);
    }

    void init_magic(void);
}
