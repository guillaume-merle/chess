#include <iostream>
#include <cassert>

#include "bitboard.hh"

namespace board
{
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

        std::cout << "\n";
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
