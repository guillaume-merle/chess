#include "gtest/gtest.h"

#include "move.hh"

TEST (move, move_to_string)
{
    board::Move move(11, 20, board::PieceType::PAWN);

    EXPECT_EQ("d2e3" ,move.to_string());
}

TEST (move, move_to_string_corner)
{
    board::Move move(7, 56, board::PieceType::PAWN);

    EXPECT_EQ("h1a8" ,move.to_string());
}

TEST (move, move_to_string_corner2)
{
    board::Move move(0, 63, board::PieceType::PAWN);

    EXPECT_EQ("a1h8" ,move.to_string());
}

TEST (move, move_to_string_queen_promotion)
{
    board::Move move(0, 63, board::PieceType::PAWN, board::PieceType::QUEEN,
        board::MoveFlag::PROMOTION);

    EXPECT_EQ("a1h8q" ,move.to_string());
}

TEST (move, move_to_string_knight_promotion)
{
    board::Move move(0, 63, board::PieceType::PAWN, board::PieceType::KNIGHT,
        board::MoveFlag::PROMOTION);

    EXPECT_EQ("a1h8n" ,move.to_string());
}

TEST (move, move_equal)
{
    board::Move lhs(0, 63, board::PieceType::PAWN);
    board::Move rhs(0, 63, board::PieceType::PAWN);

    EXPECT_TRUE(lhs == rhs);
}

TEST (move, move_not_equal)
{
    board::Move lhs(0, 63, board::PieceType::PAWN);
    board::Move rhs(0, 63, board::PieceType::KING);

    EXPECT_FALSE(lhs == rhs);
}
