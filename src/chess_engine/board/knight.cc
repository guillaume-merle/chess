#include "knight.hh"

namespace board
{
    Bitboard Knight::northwestwest(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northwest(west(bitboard, 1), 1);
        return southwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::northeasteast(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northeast(east(bitboard, 1), 1);
        return southeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::northnorthwest(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northwest(north(bitboard, 1), 1);
        return southwest(south(bitboard, 1), 1);
    }

    Bitboard Knight::northnortheast(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northeast(north(bitboard, 1), 1);
        return southeast(south(bitboard, 1), 1);
    }

    Bitboard Knight::southwestwest(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return southwest(west(bitboard, 1), 1);
        return northwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::southeasteast(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return southeast(east(bitboard, 1), 1);
        return northeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::southsouthwest(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return southwest(south(bitboard, 1), 1);
        return northwest(north(bitboard, 1), 1);
    }

    Bitboard Knight::southsoutheast(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return southeast(south(bitboard, 1), 1);
        return northeast(north(bitboard, 1), 1);
    }

    /*std::vector<Move>
    Knight::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {

    }*/
}
