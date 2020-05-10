#include "attacks.hh"

namespace board
{
    namespace attacks
    {
        Bitboard get_bishop_attacks(const unsigned int square,
                                    const Bitboard occupancy)
        {
            return *(magicmoves_b_indices[square] +
                    (((occupancy&magicmoves_b_mask[square])
                      * magicmoves_b_magics[square])
                        >> magicmoves_b_shift[square]));
        }

        Bitboard get_rook_attacks(const unsigned int square,
                                  const Bitboard occupancy)
        {
            return *(magicmoves_r_indices[square] +
                    (((occupancy&magicmoves_r_mask[square])
                      * magicmoves_r_magics[square])
                        >> magicmoves_r_shift[square]));
        }

        Bitboard get_queen_attacks(const unsigned int square,
                                   const Bitboard occupancy)
        {
            return get_bishop_attacks(square, occupancy)
                   | get_rook_attacks(square, occupancy);
        }
    }
}
