#include "gtest/gtest.h"

#include "attacks.hh"

TEST (Attacks, knight_attacks)
{
    auto moves = board::attacks::get_knight_attacks(7);

    board::Bitboard expected_moves = 1 << 13 | 1 << 22;

    EXPECT_EQ(moves, expected_moves);
}


