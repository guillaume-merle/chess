#include "attacks.hh"
#include "knight.hh"

namespace board
{
    Bitboard attacks::get_bishop_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return *(magicmoves_b_indices[square] +
                (((occupancy&magicmoves_b_mask[square])
                  * magicmoves_b_magics[square])
                 >> magicmoves_b_shift[square]));
    }

    Bitboard attacks::get_rook_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return *(magicmoves_r_indices[square] +
                (((occupancy&magicmoves_r_mask[square])
                  * magicmoves_r_magics[square])
                 >> magicmoves_r_shift[square]));
    }

    Bitboard attacks::get_queen_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return get_bishop_attacks(square, occupancy)
            | get_rook_attacks(square, occupancy);
    }

    Bitboard attacks::get_knight_attacks(const unsigned int square)
    {
        return _knight_attacks[square];
    }

    void attacks::init_knight_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1 << i;
            Bitboard attacks =
                Knight::northeasteast(pos) | Knight::northeasteast(pos)
                | Knight::southwestwest(pos) | Knight::southeasteast(pos)
                | Knight::northnorthwest(pos) | Knight::northnortheast(pos)
                | Knight::southsouthwest(pos) | Knight::southsoutheast(pos);

            _knight_attacks[i] = attacks;
        }
    }
}
