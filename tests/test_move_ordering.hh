#include "gtest/gtest.h"

#include "move-ordering.hh"

TEST (MoveOrdering, move_grade)
{
    Chessboard board;
    auto move = board::Move(8, 15, board::PAWN, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    std::vector<Move> moves;
    moves.emplace_back(move);

    ai::MoveHeuristics heuristics;
    auto move_ordering = ai::MoveOrdering(moves, heuristics, board);
    EXPECT_EQ(4000 + 29, move_ordering.get().at(0).get_grade());
}

TEST (MoveOrdering, move_ordering)
{
    Chessboard board;
    auto move = board::Move(8, 15, board::PAWN, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    auto move2 = board::Move(10, 15, board::BISHOP, board::QUEEN,
                            board::MoveFlag::CAPTURE);

    std::vector<Move> moves;
    moves.emplace_back(move);
    moves.emplace_back(move2);

    ai::MoveHeuristics heuristics;
    auto move_ordering = ai::MoveOrdering(moves, heuristics, board);
    EXPECT_EQ(board::PAWN, move_ordering.get().at(0).get_piece());
    EXPECT_EQ(board::BISHOP, move_ordering.get().at(1).get_piece());
}
