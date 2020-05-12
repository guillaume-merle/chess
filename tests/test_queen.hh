#include "gtest/gtest.h"
#include "movegen.hh"

// Only 1 test since the queen is based on the bishop and the rook

TEST (Queen, generate_moves)
{
    board::Chessboard board;
    board.set(board::WHITE, board::QUEEN, 1 << 28);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(27, moves.size());
}

TEST (Queen, generate_moves_with_chessboard)
{
    board::Chessboard board;
    board.set(board::WHITE, board::QUEEN, 1);
    board.update_all_boards();
    board.set(board::WHITE, board::ALL, 1 | 1 << 18);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(15, moves.size());
}

TEST (Queen, generate_moves_with_chessboard_multiple_blockers)
{
    board::Chessboard board;
    board.set(board::WHITE, board::QUEEN, 1);
    board.update_all_boards();
    board::Bitboard blockers = 1 | 1 << 18 | 1 << 5 | 1ULL << 32;
    board.set(board::WHITE, board::ALL, blockers);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(8, moves.size());
}

TEST (Queen, generate_moves_with_chessboard_capture)
{
    board::Chessboard board;
    board::Bitboard pawns = 1 << 8;

    board.set(board::WHITE, board::QUEEN, 1);
    board.set(board::BLACK, board::PAWN, pawns);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(15, moves.size());
    EXPECT_EQ(8, moves.at(0).get_to());
    EXPECT_TRUE(moves.at(0).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(0).get_capture());
}

TEST (Queen, generate_moves_with_chessboard_capture_multiple)
{
    board::Chessboard board;

    board.set(board::WHITE, board::QUEEN, 1);
    board::Bitboard pawns = 1 << 1 | 1 << 8 | 1 << 9;
    board.set(board::BLACK, board::PAWN, pawns);

    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
    for (auto& move : moves)
    {
        EXPECT_TRUE(move.is_capture());
        EXPECT_EQ(board::PieceType::PAWN, move.get_capture());
    }
}
