#include <iostream>

#include "knight.hh"

namespace board
{
    Bitboard Knight::northwestwest(Bitboard bitboard)
    {
        if (bitboard & (FileABB | FileBBB))
            return 0;
        return northwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::northeasteast(Bitboard bitboard)
    {
        if (bitboard & (FileHBB | FileGBB))
            return 0;
        return northeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::northnorthwest(Bitboard bitboard)
    {
        if (bitboard & FileABB)
            return 0;
        return northwest(north(bitboard, 1), 1);
    }

    Bitboard Knight::northnortheast(Bitboard bitboard)
    {
        if (bitboard & FileHBB)
            return 0;
        return northeast(north(bitboard, 1), 1);
    }

    Bitboard Knight::southwestwest(Bitboard bitboard)
    {
        if (bitboard & (FileABB | FileBBB))
            return 0;
        return southwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::southeasteast(Bitboard bitboard)
    {
        if (bitboard & (FileHBB | FileHBB))
            return 0;
        return southeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::southsouthwest(Bitboard bitboard)
    {
        if (bitboard & FileABB)
            return 0;
        return southwest(south(bitboard, 1), 1);
    }

    Bitboard Knight::southsoutheast(Bitboard bitboard)
    {
        if (bitboard & FileHBB)
            return 0;
        return southeast(south(bitboard, 1), 1);
    }

    std::vector<Move>
    Knight::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        add_move(moves, bitboard, northnorthwest(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, northnortheast(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, southsouthwest(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, southsoutheast(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, northwestwest(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, northeasteast(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, southwestwest(bitboard), PieceType::KNIGHT);

        add_move(moves, bitboard, southeasteast(bitboard), PieceType::KNIGHT);

        return moves;
    }
}
