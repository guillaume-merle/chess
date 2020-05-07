#include "gtest/gtest.h"

#include "rook.hh"

TEST (Rook, generate_moves)
{
    board::Bitboard rook = 1 << 28;
    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook);

    EXPECT_EQ(14, moves.size());
}

TEST (Rook, generate_moves_northwest)
{
    board::Bitboard rook = 1ULL << 56;
    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook);

    EXPECT_EQ(14, moves.size());

    board::Bitboard expected_moves = 0;
    for (board::Bitboard pos = board::south(rook); pos; pos = board::south(pos))
        expected_moves |= pos;
    for (board::Bitboard pos = board::east(rook); pos; pos = board::east(pos))
        expected_moves |= pos;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}

TEST (Rook, generate_moves_southeast)
{
    board::Bitboard rook = 1 << 7;
    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook);

    EXPECT_EQ(14, moves.size());

    board::Bitboard expected_moves = 0;
    for (board::Bitboard pos = board::north(rook); pos; pos = board::north(pos))
        expected_moves |= pos;
    for (board::Bitboard pos = board::west(rook); pos; pos = board::west(pos))
        expected_moves |= pos;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}
