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
    board.set(board::WHITE, board::ALL, 1 << 18);

    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, queen, board);

    EXPECT_EQ(15, moves.size());
}

TEST (Queen, generate_moves_with_chessboard_multiple_blockers)
{
    board::Bitboard queen = 1;
    board::Chessboard board;
    board::Bitboard blockers = 1 << 18 | 1 << 5 | 1ULL << 32;
    board.set(board::WHITE, board::ALL, blockers);

    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, queen, board);

    EXPECT_EQ(8, moves.size());
}

TEST (Queen, generate_moves_with_chessboard_capture)
{
    board::Bitboard queen = 1;
    board::Chessboard board;

    board::Bitboard pawns = 1 << 8;
    board.set(board::BLACK, board::PAWN, pawns);
    board.set(board::BLACK, board::ALL, pawns);

    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, queen, board);

    EXPECT_EQ(15, moves.size());
    EXPECT_EQ(1 << 8, moves.at(0).get_to());
    EXPECT_TRUE(moves.at(0).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(0).get_capture());
}

TEST (Queen, generate_moves_with_chessboard_capture_multiple)
{
    board::Bitboard queen = 1;
    board::Chessboard board;

    board::Bitboard pawns = 1 << 1 | 1 << 8 | 1 << 9;
    board.set(board::BLACK, board::PAWN, pawns);
    board.set(board::BLACK, board::ALL, pawns);

    std::vector<board::Move> moves;
    board::Queen::generate_moves(moves, queen, board);

    EXPECT_EQ(3, moves.size());
    for (auto& move : moves)
    {
        EXPECT_TRUE(move.is_capture());
        EXPECT_EQ(board::PieceType::PAWN, move.get_capture());
    }
}
