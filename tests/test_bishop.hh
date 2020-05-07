#include "gtest/gtest.h"

#include "bishop.hh"


TEST (Bishop, generate_moves)
{
    board::Bitboard bishop = 1 << 28;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(13, moves.size());
}

TEST (Bishop, generate_moves_northwest)
{
    board::Bitboard bishop = 1ULL << 56;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::southeast(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_northeast)
{
    board::Bitboard bishop = 1ULL << 63;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::southwest(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_southwest)
{
    board::Bitboard bishop = 1;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::northeast(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_southeast)
{
    board::Bitboard bishop = 1 << 7;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::northwest(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}
