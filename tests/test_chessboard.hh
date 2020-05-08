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
