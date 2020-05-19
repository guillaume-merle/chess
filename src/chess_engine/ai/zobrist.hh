#pragma once

#include "move.hh"

namespace board
{
    class Chessboard;
    /**
     * @brief Class representing a Zobrist hashing algorithm
     * to produce 64 bits keys from a Chessboard.
     *
     */
    class Zobrist
    {
    public:
        /**
         * @brief Default constructor, setting a null key.
         */
        Zobrist() = default;
        /**
         * @brief Construct a Zobrist object from a board, and hashes a key.
         */
        Zobrist(Chessboard& board);

        /**
         * @brief Initialize the different arrays with random key values.
         */
        static void init();

        /**
         * @brief update the key for the given piece.
         *
         * @param color the color of the piece.
         * @param piece the type of the piece.
         * @param pos the position to update.
         */
        void update_piece(Color color, PieceType piece, Square pos);

        /**
         * @brief update the key with the en_passant value.
         *
         * @param pos the position of the en_passant.
         */
        void update_en_passant(Square from);

        /**
         * @brief Switch the turn color.
         */
        void switch_turn();

        /**
         * @brief Unset a certain castling right.
         *
         * @param color of the side.
         * @param side the type of castling.
         */
        void unset_castling(Color color, PieceType side);

        /**
         * @brief Get the Zobrist key.
         *
         * @return the key.
         */
        uint64_t get();

    private:
        /**
         * @brief Key representing a whole Chessboard.
         */
        uint64_t key_ = 0;

        /**
         * @brief Last en_passant value of the board.
         */
        Square en_passant_square_ = -1;

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

} // namespace board
