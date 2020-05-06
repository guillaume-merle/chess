#include "queen.hh"
#include "rook.hh"
#include "bishop.hh"

namespace board
{
    std::vector<Move>
    Queen::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Rook::generate_moves(moves, bitboard);
        Bishop::generate_moves(moves, bitboard);
        return moves;
    }
}
