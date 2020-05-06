#include "rook.hh"

namespace board
{
    std::vector<Move>
    Rook::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        for (Bitboard pos = bitboard; pos; pos = north(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        for (Bitboard pos = bitboard; pos; pos = south(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        for (Bitboard pos = bitboard; pos; pos = east(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);

            // if the rook is on FileH
            if (pos & FileHBB)
                break;
        }

        for (Bitboard pos = bitboard; pos; pos = west(pos, 1))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);

            // if the rook is on FileA
            if (pos & FileABB)
                break;
        }

        return moves;
    }
}
