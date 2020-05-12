#include "knight.hh"

namespace board
{
    Bitboard Knight::northwestwest(Bitboard bitboard)
    {
        return northwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::northeasteast(Bitboard bitboard)
    {
        return northeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::northnorthwest(Bitboard bitboard)
    {
        return northwest(north(bitboard, 1), 1);
    }

    Bitboard Knight::northnortheast(Bitboard bitboard)
    {
        return northeast(north(bitboard, 1), 1);
    }

    Bitboard Knight::southwestwest(Bitboard bitboard)
    {
        return southwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::southeasteast(Bitboard bitboard)
    {
        return southeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::southsouthwest(Bitboard bitboard)
    {
        return southwest(south(bitboard, 1), 1);
    }

    Bitboard Knight::southsoutheast(Bitboard bitboard)
    {
        return southeast(south(bitboard, 1), 1);
    }
}
