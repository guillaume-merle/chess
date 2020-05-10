#include <iostream>
#include <cassert>

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
        // if piece is on FileH col
        if (bitboard << (9 * (number - 1)) & FileHBB)
            return 0;
        return bitboard << 9 * number;
    }

    Bitboard northwest(Bitboard bitboard, unsigned number)
    {
        // if piece is on FileA col
        if (bitboard << (7 * (number - 1)) & FileABB)
            return 0;
        return bitboard << 7 * number;
    }

    Bitboard southeast(Bitboard bitboard, unsigned number)
    {
        // if piece is on FileH col
        if (bitboard  >> (7 * (number - 1))& FileHBB)
            return 0;
        return bitboard >> 7 * number;
    }

    Bitboard southwest(Bitboard bitboard, unsigned number)
    {
        // if piece is on FileA col
        if (bitboard >> (9 * (number - 1)) & FileABB)
            return 0;
        return bitboard >> 9 * number;
    }

    Bitboard east(Bitboard bitboard, unsigned number)
    {
        // if piece is on FileH col
        if (bitboard << (number - 1) & FileHBB)
            return 0;
        return bitboard << number;
    }

    Bitboard west(Bitboard bitboard, unsigned number)
    {
        // if piece is on FileA col
        if (bitboard >> (number - 1) & FileABB)
            return 0;
        return bitboard >> number;
    }

    void print_bitboard(Bitboard bitboard)
    {
        for (int i = 63; i >= 0; i--)
        {
            Bitboard current = 1ULL << i;

            if (bitboard & current)
                std::cout << "1";
            else
                std::cout << ".";

            if (i % 8 == 0)
                std::cout << "\n";
            else
                std::cout << " ";
        }
    }

    int bitscan(Bitboard board)
    {
        return __builtin_ctzll(board);
    }

    int bitscan_reverse(Bitboard board)
    {
        return __builtin_clzll(board);
    }

    int pop(Bitboard& board)
    {
        assert(board);
        int square = bitscan(board);
        board &= board - 1;

        return square;
    }

    int popcount(Bitboard board)
    {
        return __builtin_popcountll(board);
    }
}
