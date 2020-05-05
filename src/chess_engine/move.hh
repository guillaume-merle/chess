#pragma once

#include "piece-type.hh"

namespace board
{
    /*
    ** \brief class of the move.
    */
    class Move
    {
    public:
        
        PieceType piece_get();

    private:

        //TODO store the move
        
        PieceType piece_;
        PieceType promotion_;
        PieceType capture_;
        bool double_pawn_push_;
        bool king_castling_;
        bool queen_castling_;
        bool en_passant_;
    };

} // namespace board
