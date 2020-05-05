#pragma once

#include <optional>

#include "chessboard-interface.hh"

namespace board
{
    /*
    ** \brief class of the chessboard.
    */
    class Chessboard : public ChessboardInterface
    {
    public:
        
        vector<Move> generate_legal_moves();

        void do_move(Move move);

        bool is_move_legal(Move move);

        bool is_check();

        bool is_checkmate();

        bool is_draw();

        //TODO operator[]

    private:
        //TODO chessboard representation

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
