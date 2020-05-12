#include "gtest/gtest.h"
#include "movegen.hh"

#include "king.hh"

TEST (King, generate_moves)
{
    board::Bitboard king = 1 << 9;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(8, moves.size());
}

TEST (King, generate_moves_only_3)
{
    board::Bitboard king = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
}

TEST (King, generate_moves_only_3_v2)
{
    board::Bitboard king = 1ULL << 63;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
}

TEST (King, generate_moves_only_5)
{
    board::Bitboard king = 1 << 8;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v2)
{
    board::Bitboard king = 1 << 15;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v3)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_only_5_v4)
{
    board::Bitboard king = 1ULL << 60;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(5, moves.size());
}

TEST (King, generate_moves_with_chessboard_none_blocking)
{
    board::Bitboard king = 1 << 9;
    board::Chessboard board;
    board.set(board::WHITE, board::ALL, king | 1ULL << 63);
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(8, moves.size());
}

TEST (King, generate_moves_with_chessboard_one_blocking)
{
    board::Bitboard king = 1 << 9;
    board::Chessboard board;
    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ALL, king | 1);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(7, moves.size());
}

TEST (King, generate_moves_with_chessboard_no_move_possible)
{
    board::Bitboard king = 1 << 9;
    board::Chessboard board;
    board.set(board::WHITE, board::ALL, board::FullBB);
    board.set(board::WHITE, board::KING, king);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(0, moves.size());
}

TEST (King, generate_moves_with_chessboard_capture)
{
    board::Bitboard king = 1;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::BLACK, board::ROOK, 1 << 1);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
    EXPECT_TRUE(moves.at(0).is_capture());
    EXPECT_EQ(board::PieceType::ROOK, moves.at(0).get_capture());
}
