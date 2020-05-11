#pragma once

#include <vector>

#include "piece-type.hh"
#include "bitboard.hh"
#include "color.hh"
#include "chessboard.hh"

namespace board
{
    enum MoveFlag : int
    {
        DOUBLE_PAWN_PUSH = 1,
        EN_PASSANT = 1 << 1,
        KING_CASTLING = 1 << 2,
        QUEEN_CASTLING = 1 << 3,
    };

    /*
    ** \brief class of the move.
    */
    class Move
    {
    public:
        Move(Bitboard from, Bitboard to, PieceType piece, int flags = 0);

        Move(Bitboard from, Bitboard to, PieceType piece, PieceType capture,
             int flags = 0);

        PieceType get_piece();

        Bitboard get_from();

        Bitboard get_to();

        PieceType get_capture();

        bool is_double_pawn_push();

        bool is_en_passant();

        bool is_capture();

        std::string to_string();

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

        void parse_flags(int flags);
    };

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece);

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece, Color color, Chessboard& board);

    Bitboard combine_moves(std::vector<Move>& moves);

} // namespace board
