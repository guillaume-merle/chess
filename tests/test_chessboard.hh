#include "gtest/gtest.h"

#include "rule.hh"
#include "move.hh"
#include "chessboard.hh"

TEST (Chessboard, is_check_by_knight)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_knight = 1 << 21;

    board.set(board::WHITE, board::KNIGHT, enemy_knight);
    board.set(board::WHITE, board::ALL, enemy_knight);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_check(board::BLACK));
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

    EXPECT_TRUE(board.is_check(board::BLACK));
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

    EXPECT_TRUE(board.is_check(board::BLACK));
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

    EXPECT_TRUE(board.is_check(board::BLACK));
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

    EXPECT_TRUE(board.is_check(board::BLACK));
}

TEST (Chessboard, is_not_check)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 22;

    board::Bitboard enemy_rook = 1 << 13 | 1ULL << 45;
    board::Bitboard enemy_bishop = 1ULL << 42;

    board.set(board::WHITE, board::ROOK, enemy_rook);
    board.set(board::WHITE, board::BISHOP, enemy_bishop);
    board.set(board::WHITE, board::ALL, enemy_rook | enemy_bishop);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_FALSE(board.is_check(board::BLACK));
}

TEST (Chessboard, is_checkmate)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 7;

    board::Bitboard enemy_rook = 1 << 4 | 1ULL << 55;
    board::Bitboard enemy_bishop = 1ULL << 42;

    board.set(board::WHITE, board::ROOK, enemy_rook);
    board.set(board::WHITE, board::BISHOP, enemy_bishop);
    board.set(board::WHITE, board::ALL, enemy_rook | enemy_bishop);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_TRUE(board.is_checkmate(board::BLACK));
}

TEST (Chessboard, scholar_checkmate)
{
    board::Chessboard board;
    board::Bitboard king = 1ULL << 60;
    board::Bitboard pawn = 1ULL << 48 | 1ULL << 49 | 1ULL << 50 | 1ULL << 51
                           | 1ULL << 54 | 1ULL << 55 | 1ULL << 36;
    board::Bitboard rook = 1ULL << 56 | 1ULL << 63;
    board::Bitboard bishop = 1ULL << 58 | 1ULL << 61;
    board::Bitboard queen = 1ULL << 59;
    board::Bitboard knight = 1ULL << 42 | 1ULL << 45;

    board::Bitboard enemy_queen = 1ULL << 53;
    board::Bitboard enemy_bishop = 1 << 26;

    board.set(board::WHITE, board::QUEEN, enemy_queen);
    board.set(board::WHITE, board::BISHOP, enemy_bishop);
    board.set(board::WHITE, board::ALL, enemy_queen | enemy_bishop);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::PAWN, pawn);
    board.set(board::BLACK, board::ROOK, rook);
    board.set(board::BLACK, board::BISHOP, bishop);
    board.set(board::BLACK, board::QUEEN, queen);
    board.set(board::BLACK, board::KNIGHT, knight);
    board.set(board::BLACK, board::ALL, king | pawn | rook | bishop | queen
                                        | knight);

    EXPECT_TRUE(board.is_checkmate(board::BLACK));
}

TEST (Chessboard, is_not_checkmate)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 6;

    board::Bitboard enemy_rook = 1ULL << 55;
    board::Bitboard enemy_bishop = 1ULL << 42;

    board.set(board::WHITE, board::ROOK, enemy_rook);
    board.set(board::WHITE, board::BISHOP, enemy_bishop);
    board.set(board::WHITE, board::ALL, enemy_rook | enemy_bishop);

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ALL, king);

    EXPECT_FALSE(board.is_checkmate(board::BLACK));
}
