#include "gtest/gtest.h"

#include "bitboard.hh"

TEST (Bitboard, north)
{
    board::Bitboard piece = 1;
    auto move = board::north(piece);

    EXPECT_EQ(1 << 8, move);
}

TEST (Bitboard, north_out)
{
    board::Bitboard piece = 1ULL << 56;
    auto move = board::north(piece);

    EXPECT_EQ(0, move);
}

TEST (Bitboard, south)
{
    board::Bitboard piece = 1ULL << 56;
    auto move = board::south(piece);

    EXPECT_EQ(1ULL << 48, move);
}

TEST (Bitboard, south_out)
{
    board::Bitboard piece = 1;
    auto move = board::south(piece);

    EXPECT_EQ(0, move);
}

TEST (Bitboard, northeast)
{
    board::Bitboard piece = 1;
    auto move = board::northeast(piece);

    EXPECT_EQ(1 << 9, move);
}

TEST (Bitboard, northeast_out)
{
    board::Bitboard piece = 1 << 7;
    auto move = board::northeast(piece);

    EXPECT_EQ(0, move);
}

TEST (Bitboard, northwest)
{
    board::Bitboard piece = 1 << 1;
    auto move = board::northwest(piece);

    EXPECT_EQ(1 << 8, move);
}

TEST (Bitboard, northwest_out)
{
    board::Bitboard piece = 1;
    auto move = board::northwest(piece);

    EXPECT_EQ(0, move);
}

TEST (Bitboard, southeast)
{
    board::Bitboard piece = 1ULL << 62;
    auto move = board::southeast(piece);

    EXPECT_EQ(1ULL << 55, move);
}

TEST (Bitboard, southeast_out)
{
    board::Bitboard piece = 1ULL << 63;
    auto move = board::southeast(piece);

    EXPECT_EQ(0, move);
}

TEST (Bitboard, southwest)
{
    board::Bitboard piece = 1ULL << 57;
    auto move = board::southwest(piece);

    EXPECT_EQ(1ULL << 48, move);
}

TEST (Bitboard, southwest_out)
{
    board::Bitboard piece = 1ULL << 56;
    auto move = board::southwest(piece);

    EXPECT_EQ(0, move);
}
