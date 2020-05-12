#include "gtest/gtest.h"

#include "bishop.hh"
#include "movegen.hh"

TEST (Bishop, generate_moves)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1 << 28);
    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(13, moves.size());
}

TEST (Bishop, generate_moves_southeast)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL << 56);
    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());

    int pos = 7;
    for (auto& move : moves)
    {
        EXPECT_EQ(pos, move.get_to());
        pos += 7;
    }
}

TEST (Bishop, generate_moves_southwest)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL << 63);
    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());

    auto pos = 0;
    for (auto& move : moves)
    {
        EXPECT_EQ(pos, move.get_to());
        pos += 9;
    }
}

TEST (Bishop, generate_moves_northeast)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1);
    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());

    auto pos = 9;
    for (auto& move : moves)
    {
        EXPECT_EQ(pos, move.get_to());
        pos += 9;
    }
}

TEST (Bishop, generate_moves_nortwest)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL << 7);
    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());
    auto pos = 14;
    for (auto& move : moves)
    {
        EXPECT_EQ(pos, move.get_to());
        pos += 7;
    }
}

TEST (Bishop, generate_moves_with_chessboard_none_blocking)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL);
    board.update_all_boards();

    board.set(board::WHITE, board::ALL, 1 << 1);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_one_blocking)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL);
    board.update_all_boards();

    board.set(board::WHITE, board::ALL, 1 << 27);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(2, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_no_move_possible)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL << 27);
    board.update_all_boards();

    board.set(board::WHITE, board::ALL, board::FullBB);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(0, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_capture)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL);

    board.set(board::BLACK, board::PAWN, 1ULL << 27);
    board.update_all_boards();

    board.set(board::BLACK, board::ALL, 1ULL << 27);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
    EXPECT_EQ(27, moves.at(0).get_to());
    EXPECT_TRUE(moves.at(0).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(0).get_capture());
}

TEST (Bishop, generate_moves_with_chessboard_capture_multiple)
{
    board::Chessboard board;
    board.set(board::WHITE, board::BISHOP, 1ULL << 9);

    board::Bitboard pawns = 1 | 1 << 2 | 1 << 16 | 1 << 18;
    board.set(board::BLACK, board::PAWN, pawns);
    board.update_all_boards();

    board.set(board::BLACK, board::ALL, pawns);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(4, moves.size());
    for (auto& move : moves)
    {
        EXPECT_TRUE(move.is_capture());
        EXPECT_EQ(board::PieceType::PAWN, move.get_capture());
    }
}
