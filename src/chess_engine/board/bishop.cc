#include "bishop.hh"
#include "move.hh"

namespace board
{
    std::vector<Move>
    Bishop::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        for (Bitboard pos = bitboard; pos; pos = northeast(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);

            // if the bishop is on FileH
            if (pos & FileHBB)
                break;
        }

        for (Bitboard pos = bitboard; pos; pos = northwest(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);

            // if the bishop is on FileA
            if (pos & FileABB)
                break;
        }

        for (Bitboard pos = bitboard; pos; pos = southeast(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);

            // if the bishop is on FileH
            if (pos & FileHBB)
                break;
        }

        for (Bitboard pos = bitboard; pos; pos = southwest(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::BISHOP);

            // if the bishop is on FileA
            if (pos & FileABB)
                break;
        }

        return moves;
    }
}
