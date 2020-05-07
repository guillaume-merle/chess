#include "gtest/gtest.h"

#include "pawn.hh"
#include "bitboard.hh"

TEST (Pawn, single_move)
{
    board::Bitboard pawn = 1 << 8;
    board::Bitboard move = board::Pawn::single_push(pawn, board::Color::WHITE);

    EXPECT_EQ(1 << 16, move);
}
