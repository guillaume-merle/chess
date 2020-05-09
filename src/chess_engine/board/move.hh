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

        Move(Bitboard from, Bitboard to, PieceType piece, PieceType capture);

        PieceType piece_get();

        Bitboard get_from();
        Bitboard get_to();
        PieceType get_capture();
        bool is_capture();

    private:
        // store the move

        Bitboard from_;
        Bitboard to_;

        PieceType piece_;
        PieceType promotion_;
        PieceType capture_;

        bool is_capture_;
        bool double_pawn_push_;
        bool king_castling_;
        bool queen_castling_;
        bool en_passant_;
    };

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece);

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece, Color color, Chessboard& board);

    Bitboard combine_moves(std::vector<Move>& moves);

} // namespace board
