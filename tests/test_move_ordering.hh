#include "gtest/gtest.h"

#include "move-ordering.hh"

TEST (MoveOrdering, move_grade)
{
    auto move = board::Move(8, 15, board::PAWN, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    std::vector<Move> moves;
    moves.emplace_back(move);

    auto move_ordering = ai::MoveOrdering(moves);
    EXPECT_EQ(4000 + 29, move_ordering.get().at(0).get_grade());
}

TEST (MoveOrdering, move_ordering)
{
    auto move = board::Move(8, 15, board::PAWN, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    auto move2 = board::Move(10, 15, board::BISHOP, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    std::vector<Move> moves;
    moves.emplace_back(move);
    moves.emplace_back(move2);

    auto move_ordering = ai::MoveOrdering(moves);
    EXPECT_EQ(board::PAWN, move_ordering.get().at(0).get_piece());
    EXPECT_EQ(board::BISHOP, move_ordering.get().at(1).get_piece());
}
