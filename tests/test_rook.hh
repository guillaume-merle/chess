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

TEST (Rook, generate_moves_with_chessboard_none_blocking)
{
    board::Bitboard rook = 1;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, 1 << 9);

    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook, board, board::Color::WHITE);

    EXPECT_EQ(14, moves.size());
}

TEST (Rook, generate_moves_with_chessboard_one_blocking)
{
    board::Bitboard rook = 1;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, 1 << 3);

    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook, board, board::Color::WHITE);

    EXPECT_EQ(9, moves.size());
}

TEST (Rook, generate_moves_with_chessboard_no_move_possible)
{
    board::Bitboard rook = 1 << 27;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, board::FullBB);

    std::vector<board::Move> moves;
    board::Rook::generate_moves(moves, rook, board, board::Color::WHITE);

    EXPECT_EQ(0, moves.size());
}
