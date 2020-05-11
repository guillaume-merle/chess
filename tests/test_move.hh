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
