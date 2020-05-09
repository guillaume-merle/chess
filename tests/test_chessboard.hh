#include "gtest/gtest.h"

#include "rule.hh"
#include "move.hh"
#include "chessboard.hh"

TEST (Chessboard, is_check)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 3;

    board::Bitboard enemy_king = 1 << 4;

    board.set(board::BitboardType::WHITEKING, king);
    board.set(board::BitboardType::ALLWHITE, king);

    board.set(board::BitboardType::BLACKKING, enemy_king);
    board.set(board::BitboardType::ALLBLACK, enemy_king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_knight)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_knight = 1 << 21;

    board.set(board::BitboardType::WHITEKNIGHT, enemy_knight);
    board.set(board::BitboardType::ALLWHITE, enemy_knight);

    board.set(board::BitboardType::BLACKKING, king);
    board.set(board::BitboardType::ALLBLACK, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_bishop)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_bishop = 1 << 25;

    board.set(board::BitboardType::WHITEBISHOP, enemy_bishop);
    board.set(board::BitboardType::ALLWHITE, enemy_bishop);

    board.set(board::BitboardType::BLACKKING, king);
    board.set(board::BitboardType::ALLBLACK, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_rook)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_rook = 1 << 7;

    board.set(board::BitboardType::WHITEROOK, enemy_rook);
    board.set(board::BitboardType::ALLWHITE, enemy_rook);

    board.set(board::BitboardType::BLACKKING, king);
    board.set(board::BitboardType::ALLBLACK, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_queen)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 4;

    board::Bitboard enemy_queen = 1ULL << 36;

    board.set(board::BitboardType::WHITEQUEEN, enemy_queen);
    board.set(board::BitboardType::ALLWHITE, enemy_queen);

    board.set(board::BitboardType::BLACKKING, king);
    board.set(board::BitboardType::ALLBLACK, king);

    EXPECT_TRUE(board.is_check());
}

TEST (Chessboard, is_check_by_pawn)
{
    board::Chessboard board;
    board::Bitboard king = 1 << 22;

    board::Bitboard enemy_pawn = 1 << 13;

    board.set(board::BitboardType::WHITEPAWN, enemy_pawn);
    board.set(board::BitboardType::ALLWHITE, enemy_pawn);

    board.set(board::BitboardType::BLACKKING, king);
    board.set(board::BitboardType::ALLBLACK, king);

    EXPECT_TRUE(board.is_check());
}
