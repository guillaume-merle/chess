#pragma once

#include "bitboard.hh"

#define MINIMAL_B_BITS_SHIFT(square) 55
#define MINIMAL_R_BITS_SHIFT(square) 52

namespace board
{
    /**
     * @brief Class containing the magic moves of the bishop and rook.
     *
     * Magic numbers and shifts are used to store moves corresponding
     * to the different occupancies.
     *
     */
    class Magic
    {
    public:
        /**
         * @brief Initialize magic moves.
         */
        Magic();

        /**
         * @brief Initialize magic moves.
         */
        Bitboard get_bishop_moves(Square square, Bitboard occupancy) const;

        /**
         * @brief Initialize magic moves.
         */
        Bitboard get_rook_moves(Square square, Bitboard occupancy) const;

    private:
        /**
         * @brief All possible bishop moves.
         */
        Bitboard bishop_moves_[5248];

        /**
         * @brief All possible rook moves.
         */
        Bitboard rook_moves_[102400];

        /**
         * @brief Initialize magic moves.
         */
        void init();

        /**
         * @brief Set a Bitboard of moves for the rook.
         */
        void set_rook_move(int square, Bitboard occupancy, Bitboard move);

        /**
         * @brief Set a Bitboard of moves for the bishop.
         */
        void set_bishop_move(int square, Bitboard occupancy, Bitboard move);
    };

    extern Magic magic;
} // namespace board
