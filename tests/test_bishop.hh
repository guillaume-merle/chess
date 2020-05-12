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

TEST (Bishop, generate_moves_northwest)
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

TEST (Bishop, generate_moves_northeast)
{
    board::Bitboard bishop = 1ULL << 63;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::southwest(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_southwest)
{
    board::Bitboard bishop = 1;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::northeast(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_southeast)
{
    board::Bitboard bishop = 1 << 7;
    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop);

    EXPECT_EQ(7, moves.size());
    auto pos = bishop;
    for (auto& move : moves)
    {
        pos = board::northwest(pos);
        EXPECT_EQ(pos, move.get_to());
    }
}

TEST (Bishop, generate_moves_with_chessboard_none_blocking)
{
    board::Bitboard bishop = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::ALL, 1 << 1);

    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop, board, board::Color::WHITE);

    EXPECT_EQ(7, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_one_blocking)
{
    board::Bitboard bishop = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::ALL, 1 << 27);

    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop, board, board::Color::WHITE);

    EXPECT_EQ(2, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_no_move_possible)
{
    board::Bitboard bishop = 1 << 27;
    board::Chessboard board;
    board.set(board::WHITE, board::ALL, board::FullBB);

    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop, board, board::Color::WHITE);

    EXPECT_EQ(0, moves.size());
}

TEST (Bishop, generate_moves_with_chessboard_capture)
{
    board::Bitboard bishop = 1;
    board::Chessboard board;

    board::Bitboard pawns = 1 << 27;
    board.set(board::BLACK, board::PAWN, pawns);
    board.set(board::BLACK, board::ALL, pawns);

    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop, board, board::Color::WHITE);

    EXPECT_EQ(3, moves.size());
    EXPECT_EQ(1 << 27, moves.at(2).get_to());
    EXPECT_TRUE(moves.at(2).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(2).get_capture());
}

TEST (Bishop, generate_moves_with_chessboard_capture_multiple)
{
    board::Bitboard bishop = 1 << 9;
    board::Chessboard board;

    board::Bitboard pawns = 1 | 1 << 2 | 1 << 16 | 1 << 18;
    board.set(board::BLACK, board::PAWN, pawns);
    board.set(board::BLACK, board::ALL, pawns);

    std::vector<board::Move> moves;
    board::Bishop::generate_moves(moves, bishop, board, board::Color::WHITE);

    EXPECT_EQ(4, moves.size());
    for (auto& move : moves)
    {
        EXPECT_TRUE(move.is_capture());
        EXPECT_EQ(board::PieceType::PAWN, move.get_capture());
    }
}
