#pragma once

#include <vector>

#include "chessboard-interface.hh"
#include "bitboard.hh"

namespace board
{
    constexpr int BITBOARDS_NUMBER = 14;

    class Move;

    enum BitboardType
    {
        ALLWHITE = 0,
        ALLBLACK,
        WHITEQUEEN,
        BLACKQUEEN,
        WHITEROOK,
        BLACKROOK,
        WHITEBISHOP,
        BLACKBISHOP,
        WHITEKNIGHT,
        BLACKKNIGHT,
        WHITEPAWN,
        BLACKPAWN,
        WHITEKING,
        BLACKKING,
    };

    /*
    ** \brief class of the chessboard.
    */
    class Chessboard : public ChessboardInterface
    {
    public:
        Chessboard()
            : bitboards_{0}, white_turn_(true)
        {}

        std::vector<Move> generate_legal_moves();

        void do_move(Move move);

        bool is_move_legal(Move move);

        bool is_check();

        bool is_checkmate();

        bool is_draw();

        Bitboard get(BitboardType piece);

        Bitboard get(int piece);

        bool set(BitboardType piece, Bitboard value);

        bool is_white_turn();

        virtual opt_piece_t operator[](const Position& position) const;

        bool would_collide(Bitboard pos, Color color);

        bool would_capture(Bitboard pos, Color color);

    private:
        Bitboard bitboards_[BITBOARDS_NUMBER];

        bool white_turn_;
        bool white_king_castling_;
        bool white_queen_castling_;
        bool black_king_castling_;
        bool black_queen_castling_;
        //en_passant_; TODO
        unsigned int turn_;
        //last_fifty_turn_; TODO
    };

} // namespace board
