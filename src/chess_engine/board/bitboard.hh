#pragma once

#include <cstdint>

namespace board
{
    using Bitboard = uint64_t;

    constexpr Bitboard FileABB = 0x0101010101010101ULL;
    constexpr Bitboard FileBBB = FileABB << 1;
    constexpr Bitboard FileCBB = FileABB << 2;
    constexpr Bitboard FileDBB = FileABB << 3;
    constexpr Bitboard FileEBB = FileABB << 4;
    constexpr Bitboard FileFBB = FileABB << 5;
    constexpr Bitboard FileGBB = FileABB << 6;
    constexpr Bitboard FileHBB = FileABB << 7;

    constexpr Bitboard Rank1BB = 0xFF;
    constexpr Bitboard Rank2BB = Rank1BB << (8 * 1);
    constexpr Bitboard Rank3BB = Rank1BB << (8 * 2);
    constexpr Bitboard Rank4BB = Rank1BB << (8 * 3);
    constexpr Bitboard Rank5BB = Rank1BB << (8 * 4);
    constexpr Bitboard Rank6BB = Rank1BB << (8 * 5);
    constexpr Bitboard Rank7BB = Rank1BB << (8 * 6);
    constexpr Bitboard Rank8BB = Rank1BB << (8 * 7);

    Bitboard north(Bitboard bitboard, unsigned number);
    Bitboard northeast(Bitboard bitboard, unsigned number);
    Bitboard northwest(Bitboard bitboard, unsigned number);
    Bitboard south(Bitboard bitboard, unsigned number);
    Bitboard southeast(Bitboard bitboard, unsigned number);
    Bitboard southwest(Bitboard bitboard, unsigned number);
    Bitboard east(Bitboard bitboard, unsigned number);
    Bitboard west(Bitboard bitboard, unsigned number);

    void print_bitboard(Bitboard bitboard);
}
