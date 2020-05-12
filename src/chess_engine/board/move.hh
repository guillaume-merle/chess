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
        PROMOTION = 1 << 4,
        CAPTURE = 1 << 5
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

        Move(Bitboard from, Bitboard to, PieceType piece, PieceType promotion,
             PieceType capture, int flags = 0);

        PieceType get_piece();

        Bitboard get_from();

        Bitboard get_to();

        PieceType get_capture();

        bool is_double_pawn_push();

        bool is_en_passant();

        bool is_capture();

        bool is_promotion();

        bool is_king_side_castling();

        bool is_queen_side_castling();

        std::string to_string();

        bool operator==(const Move& rhs) const;

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
        bool is_promotion_;

        void parse_flags(int flags);
    };

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece);

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece, Color color, Chessboard& board);

    Bitboard combine_moves(std::vector<Move>& moves);

} // namespace board
