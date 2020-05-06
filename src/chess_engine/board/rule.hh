#pragma once

#include "chessboard.hh"

namespace board
{
    std::vector<Move> generate_pawn_moves(Chessboard& chessboard);
    std::vector<Move> generate_king_moves(Chessboard& chessboard);
}
