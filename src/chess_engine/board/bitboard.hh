#pragma once

#include <cstdint>

namespace board
{
    using Bitboard = uint64_t;
    using Square = int;

    const Bitboard FileABB = 0x0101010101010101ULL;
    const Bitboard FileBBB = FileABB << 1;
    const Bitboard FileCBB = FileABB << 2;
    const Bitboard FileDBB = FileABB << 3;
    const Bitboard FileEBB = FileABB << 4;
    const Bitboard FileFBB = FileABB << 5;
    const Bitboard FileGBB = FileABB << 6;
    const Bitboard FileHBB = FileABB << 7;

    const Bitboard Rank1BB = 0xFF;
    const Bitboard Rank2BB = Rank1BB << (8 * 1);
    const Bitboard Rank3BB = Rank1BB << (8 * 2);
    const Bitboard Rank4BB = Rank1BB << (8 * 3);
    const Bitboard Rank5BB = Rank1BB << (8 * 4);
    const Bitboard Rank6BB = Rank1BB << (8 * 5);
    const Bitboard Rank7BB = Rank1BB << (8 * 6);
    const Bitboard Rank8BB = Rank1BB << (8 * 7);

    const Bitboard EmptyFileABB = 0xFEFEFEFEFEFEFEFE;
    const Bitboard EmptyFileHBB = 0x7F7F7F7F7F7F7F7F;

    const Bitboard FullBB = 0xFFFFFFFFFFFFFFFF;

    inline Bitboard north(Bitboard bitboard, unsigned number = 1)
    {
        return bitboard << 8 * number;
    }

    inline Bitboard south(Bitboard bitboard, unsigned number = 1)
    {
        return bitboard >> 8 * number;
    }

    inline Bitboard northeast(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileH col
        if (bitboard << (9 * (number - 1)) & FileHBB)
            return 0;
        return bitboard << 9 * number;
    }

    inline Bitboard northwest(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileA col
        if (bitboard << (7 * (number - 1)) & FileABB)
            return 0;
        return bitboard << 7 * number;
    }

    inline Bitboard southeast(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileH col
        if (bitboard  >> (7 * (number - 1))& FileHBB)
            return 0;
        return bitboard >> 7 * number;
    }

    inline Bitboard southwest(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileA col
        if (bitboard >> (9 * (number - 1)) & FileABB)
            return 0;
        return bitboard >> 9 * number;
    }

    inline Bitboard east(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileH col
        if (bitboard << (number - 1) & FileHBB)
            return 0;
        return bitboard << number;
    }

    inline Bitboard west(Bitboard bitboard, unsigned number = 1)
    {
        // if piece is on FileA col
        if (bitboard >> (number - 1) & FileABB)
            return 0;
        return bitboard >> number;
    }

    int bitscan(Bitboard board);
    int bitscan_reverse(Bitboard board);
    int pop(Bitboard& board);
    int popcount(Bitboard board);

    void print_bitboard(Bitboard bitboard);
}
