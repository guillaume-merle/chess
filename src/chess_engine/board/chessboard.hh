#pragma once

#include <vector>

#include "chessboard-interface.hh"
#include "move.hh"
#include "bitboard.hh"

namespace board
{
    enum BitboardPiece
    {
        ALLWHITE = 0,
        ALLBLACK,
        WHITEPAWN,
        BLACKPAWN,
        WHITEQUEEN,
        BLACKQUEEN,
        WHITEKING,
        BLACKKING,
        WHITEROOK,
        BLACKROOK,
        WHITEBISHOP,
        BLACKBISHOP,
        WHITEKNIGHT,
        BLACKKNIGHT
    };

    /*
    ** \brief class of the chessboard.
    */
    class Chessboard : public ChessboardInterface
    {
    public:

        std::vector<Move> generate_legal_moves();

        void do_move(Move move);

        bool is_move_legal(Move move);

        bool is_check();

        bool is_checkmate();

        bool is_draw();

        Bitboard get_bitboard(BitboardPiece piece);

        bool is_white_turn();

        virtual opt_piece_t operator[](const Position& position) const;

    private:
        //TODO chessboard representation
        Bitboard bitboards_[14];

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
