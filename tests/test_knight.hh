#include "gtest/gtest.h"

#include "knight.hh"

TEST (Knight, basic_northnortheast)
{
    board::Bitboard knight = 1 << 5;
    board::Bitboard move = board::Knight::northnortheast(knight,
                                                         board::Color::WHITE);
    EXPECT_EQ(1 << 22, move);
}

TEST (Knight, basic_northnorthwest)
{
    board::Bitboard knight = 1 << 9;
    board::Bitboard move = board::Knight::northnorthwest(knight,
                                                         board::Color::WHITE);
    EXPECT_EQ(1 << 24, move);
}

TEST (Knight, basic_northeasteast)
{
    board::Bitboard knight = 1ULL << 32;
    board::Bitboard move = board::Knight::northeasteast(knight,
                                                        board::Color::WHITE);
    EXPECT_EQ(1ULL << 42, move);
}

TEST (Knight, basic_northwestwest)
{
    board::Bitboard knight = 1 << 27;
    board::Bitboard move = board::Knight::northwestwest(knight,
                                                        board::Color::WHITE);
    EXPECT_EQ(1ULL << 33, move);
}

TEST (Knight, basic_southsoutheast)
{
    board::Bitboard knight = 1ULL << 51;
    board::Bitboard move = board::Knight::southsoutheast(knight,
                                                         board::Color::WHITE);
    EXPECT_EQ(1ULL << 36, move);
}

TEST (Knight, basic_southsouthwest)
{
    board::Bitboard knight = 1ULL << 60;
    board::Bitboard move = board::Knight::southsouthwest(knight,
                                                         board::Color::WHITE);
    EXPECT_EQ(1ULL << 43, move);
}

TEST (Knight, basic_southeasteast)
{
    board::Bitboard knight = 1 << 13;
    board::Bitboard move = board::Knight::southeasteast(knight,
                                                        board::Color::WHITE);
    EXPECT_EQ(1 << 7, move);
}

TEST (Knight, basic_southwestwest)
{
    board::Bitboard knight = 1 << 29;
    board::Bitboard move = board::Knight::southwestwest(knight,
                                                        board::Color::WHITE);
    EXPECT_EQ(1 << 19, move);
}
