#pragma once

#include <vector>
#include <string>

#include "piece-type.hh"
#include "bitboard.hh"
#include "color.hh"

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
        Move();

        explicit Move(Bitboard from, Bitboard to, PieceType piece,
                      int flags = 0);

        explicit Move(Bitboard from, Bitboard to, PieceType piece,
                      PieceType capture, int flags = 0);

        explicit Move(Bitboard from, Bitboard to, PieceType piece,
                      PieceType promotion, PieceType capture, int flags = 0);

        PieceType get_piece();

        Bitboard get_from();

        Bitboard get_to();

        PieceType get_capture();

        PieceType get_promotion();

        bool is_double_pawn_push();

        bool is_en_passant();

        bool is_capture();

        bool is_promotion();

        bool is_king_side_castling();

        bool is_queen_side_castling();

        bool is_none();

        void set_grade(int grade);

        int get_grade();

        std::string to_string();

        bool operator==(const Move& rhs) const;

    private:
        // store the move
        Square from_;

        Square to_;

        PieceType piece_;

        PieceType promotion_;

        PieceType capture_;

        bool is_capture_;

        bool double_pawn_push_;

        bool king_castling_;

        bool queen_castling_;

        bool en_passant_;

        bool is_promotion_;

        bool none_ = false;

        /**
         * @brief grade of the move for move-ordering.
         */
        int grade_ = 0;

        void parse_flags(int flags);
    };

    Bitboard combine_moves(std::vector<Move>& moves);

} // namespace board
