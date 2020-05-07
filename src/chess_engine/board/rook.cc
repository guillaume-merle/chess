#include "rook.hh"

namespace board
{
    std::vector<Move>
    Rook::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Bitboard pos = north(bitboard);
        for (; pos; pos = north(pos))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        pos = south(bitboard);
        for (; pos; pos = south(pos))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        pos = east(bitboard);
        for (; pos; pos = east(pos))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        pos = west(bitboard);
        for (; pos; pos = west(pos))
        {
            add_move(moves, bitboard, pos, PieceType::ROOK);
        }

        return moves;
    }
}
