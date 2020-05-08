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

TEST (Queen, generate_moves_with_chessboard)
{
    board::Bitboard queen = 1;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, 1 << 18);

    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, queen, board);

    EXPECT_EQ(15, moves.size());
}
