#pragma once

#include <cstdint>

namespace board
{
    using Bitboard = uint64_t;

    Bitboard north(Bitboard bitboard, unsigned number);
    Bitboard northeast(Bitboard bitboard, unsigned number);
    Bitboard northwest(Bitboard bitboard, unsigned number);
    Bitboard south(Bitboard bitboard, unsigned number);
    Bitboard southeast(Bitboard bitboard, unsigned number);
    Bitboard southwest(Bitboard bitboard, unsigned number);
    Bitboard east(Bitboard bitboard, unsigned number);
    Bitboard west(Bitboard bitboard, unsigned number);
}
