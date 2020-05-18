#pragma once

#include "chessboard.hh"

using namespace board;

namespace ai
{
    /**
     * @brief Class representing a Zobrist hashing to produce 64 bits keys
     * from a Chessboard.
     *
     */
    class Zobrist
    {
    public:
        /**
         * @brief Construct a Zobrist object from a board, and hashes a key.
         */
        Zobrist(Chessboard& board);

    private:
        /**
         * @brief Key representing a whole Chessboard.
         */
        uint64_t key_;

        /**
         * @brief Keys for all the pieces of each color at each position,
         * stored as [Color][PieceType][Square]
         */
        static uint64_t pieces_[2][6][64];

        /**
         * @brief Key for the current color.
         */
        static uint64_t white_turn_;

        /**
         * @brief Keys for the king side castling.
         */
        static uint64_t king_side_castling_[2];

        /**
         * @brief Keys for the queen side castling.
         */
        static uint64_t queen_side_castling_[2];

        /**
         * @brief Keys for the en passant square, stored by File index.
         */
        static uint64_t en_passant_[8];
    };
}
