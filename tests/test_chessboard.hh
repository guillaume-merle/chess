#include "gtest/gtest.h"

#include "rule.hh"
#include "move.hh"
#include "chessboard.hh"

TEST (Chessboard, is_check)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 3;

    board::Bitboard enemy_king = 1 << 4;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ALL, king);

    board.set(board::BLACK, board::KING, enemy_king);
    board.set(board::BLACK, board::ALL, enemy_king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_knight)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_knight = 1 << 21;

    board.set(board::WHITE, board::KNIGHT, enemy_knight);
    board.set(board::WHITE, board::ALL, enemy_knight);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_bishop)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_bishop = 1 << 25;

    board.set(board::WHITE, board::BISHOP, enemy_bishop);
    board.set(board::WHITE, board::ALL, enemy_bishop);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_rook)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_rook = 1 << 7;

    board.set(board::WHITE, board::ROOK, enemy_rook);
    board.set(board::WHITE, board::ALL, enemy_rook);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_queen)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_queen = 1ULL << 36;

    board.set(board::WHITE, board::QUEEN, enemy_queen);
    board.set(board::WHITE, board::ALL, enemy_queen);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_pawn)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 22;

    board::Bitboard enemy_pawn = 1 << 13;

    board.set(board::WHITE, board::PAWN, enemy_pawn);
    board.set(board::WHITE, board::ALL, enemy_pawn);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check());
}
