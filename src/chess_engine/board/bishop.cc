#include "bishop.hh"
#include "move.hh"

namespace board
{
    std::vector<Move>
    Bishop::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Bitboard pos = northeast(bitboard, 1);
        for (; pos; pos = northeast(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);
        }

        pos = northwest(bitboard, 1);
        for (; pos; pos = northwest(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);
        }

        pos = southeast(bitboard, 1);
        for (; pos; pos = southeast(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);
        }

        pos = southwest(bitboard, 1);
        for (; pos; pos = southwest(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);
        }

        return moves;
    }
}
