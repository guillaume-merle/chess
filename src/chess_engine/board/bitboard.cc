#include "bitboard.hh"

namespace board
{
    Bitboard north(Bitboard bitboard, unsigned number)
    {
        return bitboard << 8 * number;
    }

    Bitboard south(Bitboard bitboard, unsigned number)
    {
        return bitboard >> 8 * number;
    }

    Bitboard northeast(Bitboard bitboard, unsigned number)
    {
        return bitboard << 9 * number;
    }

    Bitboard northwest(Bitboard bitboard, unsigned number)
    {
        return bitboard << 7 * number;
    }

    Bitboard southeast(Bitboard bitboard, unsigned number)
    {
        return bitboard >> 7 * number;
    }

    Bitboard southwest(Bitboard bitboard, unsigned number)
    {
        return bitboard >> 9 * number;
    }

    Bitboard east(Bitboard bitboard, unsigned number)
    {
        return bitboard << number;
    }

    Bitboard west(Bitboard bitboard, unsigned number)
    {
        return bitboard >> number;
    }
}
