#pragma once

#include "chessboard.hh"

namespace board
{
    std::vector<Move> generate_pawn_moves(Chessboard& chessboard);
    std::vector<Move> generate_king_moves(Chessboard& chessboard);
    std::vector<Move> generate_bishop_moves(Chessboard& chessboard);
    std::vector<Move> generate_rook_moves(Chessboard& chessboard);
    std::vector<Move> generate_queen_moves(Chessboard& chessboard);
    std::vector<Move> generate_knight_moves(Chessboard& chessboard);
}
