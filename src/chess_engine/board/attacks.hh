#pragma once

#include "magic.hh"
#include "color.hh"

namespace board
{
    /**
     * @brief Class containing the attacks of all pieces.
     *
     */
    class Attacks
    {
    public:
        /**
         * @brief Initialize all attacks for all pieces.
         */
        Attacks();

        Bitboard get_bishop_attacks(const Square square,
                                    const Bitboard occupancy) const;

        Bitboard get_rook_attacks(const Square square,
                                  const Bitboard occupancy) const;

        Bitboard get_queen_attacks(const Square square,
                                   const Bitboard occupancy) const;

        Bitboard get_knight_attacks(const Square square) const;

        Bitboard get_king_attacks(const Square square) const;

        Bitboard get_pawn_attacks(const Square square, Color color) const;

    private:
        Bitboard knight_attacks_[64];

        Bitboard king_attacks_[64];

        Bitboard pawn_attacks_[2][64];

        Magic magic_;

        void init_knight_attacks();

        void init_king_attacks();

        void init_pawn_attacks();
    };

    extern Attacks attacks_g;
}
