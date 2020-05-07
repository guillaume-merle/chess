#include "gtest/gtest.h"

#include "pawn.hh"
#include "bitboard.hh"

TEST (Pawn, single_push_white)
{
    board::Bitboard pawn = 1 << 8;
    board::Bitboard move = board::Pawn::single_push(pawn, board::Color::WHITE);

    EXPECT_EQ(1 << 16, move);
}

TEST (Pawn, single_push_black)
{
    board::Bitboard pawn = 1ULL << 48;
    board::Bitboard move = board::Pawn::single_push(pawn, board::Color::BLACK);

    EXPECT_EQ(1ULL << 40, move);
}

TEST (Pawn, double_push_white)
{
    board::Bitboard pawn = 1 << 8;
    board::Bitboard move = board::Pawn::double_push(pawn, board::Color::WHITE);

    EXPECT_EQ(1ULL << 24, move);
}

TEST (Pawn, double_push_black)
{
    board::Bitboard pawn = 1ULL << 48;
    board::Bitboard move = board::Pawn::double_push(pawn, board::Color::BLACK);

    EXPECT_EQ(1ULL << 32, move);
}
