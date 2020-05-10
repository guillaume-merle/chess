#include "gtest/gtest.h"

#include "attacks.hh"

TEST (Attacks, knight_attacks)
{
    auto moves = board::attacks::get_knight_attacks(7);

    board::Bitboard expected_moves = 1 << 13 | 1 << 22;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, knight_attacks2)
{
    auto moves = board::attacks::get_knight_attacks(26);

    board::Bitboard expected_moves = 1 << 16 | 1ULL << 32 | 1ULL << 41
                                     | 1ULL << 43 | 1ULL << 36 | 1 << 20
                                     | 1 << 9 | 1 << 11;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, king_attacks)
{
    auto moves = board::attacks::get_king_attacks(63);

    board::Bitboard expected_moves = 1ULL << 62 | 1ULL << 54 | 1ULL << 55;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, king_attacks2)
{
    auto moves = board::attacks::get_king_attacks(11);

    board::Bitboard expected_moves = 1 << 2 | 1 << 3 | 1 << 4 | 1 << 12
                                     | 1 << 10 | 1 << 18 | 1 << 19 | 1 << 20;

    EXPECT_EQ(moves, expected_moves);
}


