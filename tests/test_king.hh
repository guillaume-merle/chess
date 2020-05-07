#include "gtest/gtest.h"

#include "king.hh"

TEST (King, generate_moves)
{
    board::Bitboard king = 1 << 9;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(8, moves.size());
    EXPECT_EQ(1 << 17, moves.at(0).get_to());
    EXPECT_EQ(1 << 1, moves.at(1).get_to());
    EXPECT_EQ(1 << 8, moves.at(2).get_to());
    EXPECT_EQ(1 << 16, moves.at(3).get_to());
    EXPECT_EQ(1, moves.at(4).get_to());
    EXPECT_EQ(1 << 10, moves.at(5).get_to());
    EXPECT_EQ(1 << 18, moves.at(6).get_to());
    EXPECT_EQ(1 << 2, moves.at(7).get_to());
}

TEST (King, generate_moves_only_3)
{
    board::Bitboard king = 1;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(3, moves.size());
}

TEST (King, generate_moves_only_3_v2)
{
    board::Bitboard king = 1ULL << 63;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(3, moves.size());
}

TEST (King, generate_moves_only_5)
{
    board::Bitboard king = 1 << 8;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v2)
{
    board::Bitboard king = 1 << 15;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v3)
{
    board::Bitboard king = 1 << 4;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v4)
{
    board::Bitboard king = 1ULL << 60;
    std::vector<board::Move> moves;
    board::King::generate_moves(moves, king);

    EXPECT_EQ(5, moves.size());
}
