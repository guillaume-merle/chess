#include "gtest/gtest.h"

#include "queen.hh"

// Only 1 test since the queen is based on the bishop and the rook

TEST (Queen, generate_moves)
{
    board::Bitboard rook = 1 << 28;
    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, rook);

    EXPECT_EQ(27, moves.size());
}
