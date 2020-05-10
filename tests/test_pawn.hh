#include "gtest/gtest.h"

#include "pawn.hh"
#include "bitboard.hh"

TEST (Pawn, single_push_white)
{
    board::Bitboard pawn = 1 << 8;
    board::Bitboard move = board::Pawn::single_push(pawn, board::Color::WHITE);

    EXPECT_EQ(1 << 16, move);
}

TEST (Pawn, single_push_black)
{
    board::Bitboard pawn = 1ULL << 48;
    board::Bitboard move = board::Pawn::single_push(pawn, board::Color::BLACK);

    EXPECT_EQ(1ULL << 40, move);
}

TEST (Pawn, double_push_white)
{
    board::Bitboard pawn = 1 << 8;
    board::Bitboard move = board::Pawn::double_push(pawn, board::Color::WHITE);

    EXPECT_EQ(1ULL << 24, move);
}

TEST (Pawn, double_push_black)
{
    board::Bitboard pawn = 1ULL << 48;
    board::Bitboard move = board::Pawn::double_push(pawn, board::Color::BLACK);

    EXPECT_EQ(1ULL << 32, move);
}

TEST (Pawn, generate_white_moves_singles)
{
    board::Bitboard pawn = 1 << 16;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE);

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(1 << 24, moves.at(0).get_to());
}

TEST (Pawn, generate_white_moves_singles_and_double)
{
    board::Bitboard pawn = 1 << 8;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE);

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(1 << 16, moves.at(0).get_to());
    EXPECT_EQ(1 << 24, moves.at(1).get_to());

}

TEST (Pawn, generate_black_moves_singles)
{
    board::Bitboard pawn = 1ULL << 40;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::BLACK);

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(1ULL << 32, moves.at(0).get_to());
}

TEST (Pawn, generate_black_moves_singles_and_double)
{
    board::Bitboard pawn = 1ULL << 48;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::BLACK);

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(1ULL << 40, moves.at(0).get_to());
    EXPECT_EQ(1ULL << 32, moves.at(1).get_to());
}

TEST (Pawn, generate_white_moves_out)
{
    board::Bitboard pawn = 1ULL << 56;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE);

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_black_moves_out)
{
    board::Bitboard pawn = 1;
    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::BLACK);

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_moves_with_chessboard_no_move)
{
    board::Bitboard pawn = 1 << 8;
    board::Chessboard board;
    board.set(board::BLACK, board::ALL, 1 << 16);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_moves_with_chessboard_single_but_not_double)
{
    board::Bitboard pawn = 1 << 8;
    board::Chessboard board;
    board.set(board::BLACK, board::ALL, 1 << 24);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(1 << 16, moves.at(0).get_to());
}

TEST (Pawn, generate_moves_with_chessboard_no_collision)
{
    board::Bitboard pawn = 1 << 8;
    board::Chessboard board;
    board.set(board::BLACK, board::ALL, 1);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(1 << 16, moves.at(0).get_to());
    EXPECT_EQ(1 << 24, moves.at(1).get_to());
}

TEST (Pawn, generate_moves_with_chessboard_capture)
{
    board::Bitboard pawn = 1 << 16;
    board::Chessboard board;

    board::Bitboard other_pawn = 1 << 25;
    board.set(board::BLACK, board::ALL, other_pawn);
    board.set(board::BLACK, board::PAWN, other_pawn);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(2, moves.size());
    EXPECT_TRUE(moves.at(1).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(1).get_capture());
}

TEST (Pawn, generate_moves_with_chessboard_capture_double_push)
{
    board::Bitboard pawn = 1 << 8;
    board::Chessboard board;

    board::Bitboard other_pawn = 1 << 17;
    board.set(board::BLACK, board::ALL, other_pawn);
    board.set(board::BLACK, board::PAWN, other_pawn);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(3, moves.size());
    EXPECT_TRUE(moves.at(2).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(2).get_capture());
}

TEST (Pawn, generate_moves_with_chessboard_capture_left_and_right)
{
    board::Bitboard pawn = 1 << 17;
    board::Chessboard board;

    board::Bitboard other_pawn = 1 << 24 | 1 << 26;
    board.set(board::BLACK, board::ALL, other_pawn);
    board.set(board::BLACK, board::PAWN, other_pawn);

    std::vector<board::Move> moves;
    board::Pawn::generate_moves(moves, pawn, board::Color::WHITE, board);

    EXPECT_EQ(3, moves.size());
    EXPECT_TRUE(moves.at(1).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(1).get_capture());
    EXPECT_TRUE(moves.at(1).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(2).get_capture());
}
