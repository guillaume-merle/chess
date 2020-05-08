#pragma once

#include <vector>

#include "piece-type.hh"
#include "bitboard.hh"
#include "color.hh"
#include "chessboard.hh"

namespace board
{
    /*
    ** \brief class of the move.
    */
    class Move
    {
    public:

        Move(Bitboard from, Bitboard to, PieceType piece);

        PieceType piece_get();

        Bitboard get_from();
        Bitboard get_to();

    private:

        // store the move

        Bitboard from_;
        Bitboard to_;

        PieceType piece_;
        PieceType promotion_;
        PieceType capture_;
        bool double_pawn_push_;
        bool king_castling_;
        bool queen_castling_;
        bool en_passant_;
    };

    void add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece);

    void add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece, Color color, Chessboard board);
    Bitboard combine_moves(std::vector<Move>& moves);

} // namespace board
