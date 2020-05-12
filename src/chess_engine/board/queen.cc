#include "queen.hh"
#include "rook.hh"
#include "bishop.hh"

namespace board
{
    std::vector<Move>
    Queen::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Chessboard board;
        return generate_moves(moves, bitboard, board);
    }

    std::vector<Move>
    Queen::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                          Chessboard& board, Color color)
    {
        Rook::generate_moves(moves, bitboard, board, color);
        Bishop::generate_moves(moves, bitboard, board, color);
        return moves;
    }
}
