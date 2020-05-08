#include "gtest/gtest.h"

#include "knight.hh"

TEST (Knight, basic_northnortheast)
{
    board::Bitboard knight = 1 << 5;
    board::Bitboard move = board::Knight::northnortheast(knight);
    EXPECT_EQ(1 << 22, move);
}

TEST (Knight, northnortheast_out)
{
    board::Bitboard knight = 1 << 23;
    board::Bitboard move = board::Knight::northnortheast(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_northnorthwest)
{
    board::Bitboard knight = 1 << 9;
    board::Bitboard move = board::Knight::northnorthwest(knight);
    EXPECT_EQ(1 << 24, move);
}

TEST (Knight, northnorthwest_out)
{
    board::Bitboard knight = 1 << 16;
    board::Bitboard move = board::Knight::northnorthwest(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_northeasteast)
{
    board::Bitboard knight = 1ULL << 32;
    board::Bitboard move = board::Knight::northeasteast(knight);
    EXPECT_EQ(1ULL << 42, move);
}

TEST (Knight, northeasteast_out)
{
    board::Bitboard knight = 1ULL << 54;
    board::Bitboard move = board::Knight::northeasteast(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_northwestwest)
{
    board::Bitboard knight = 1 << 27;
    board::Bitboard move = board::Knight::northwestwest(knight);
    EXPECT_EQ(1ULL << 33, move);
}

TEST (Knight, northwestwest_out)
{
    board::Bitboard knight = 1 << 25;
    board::Bitboard move = board::Knight::northwestwest(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_southsoutheast)
{
    board::Bitboard knight = 1ULL << 51;
    board::Bitboard move = board::Knight::southsoutheast(knight);
    EXPECT_EQ(1ULL << 36, move);
}

TEST (Knight, southsoutheast_out)
{
    board::Bitboard knight = 1ULL << 47;
    board::Bitboard move = board::Knight::southsoutheast(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_southsouthwest)
{
    board::Bitboard knight = 1ULL << 60;
    board::Bitboard move = board::Knight::southsouthwest(knight);
    EXPECT_EQ(1ULL << 43, move);
}

TEST (Knight, southsouthwest_out)
{
    board::Bitboard knight = 1ULL << 56;
    board::Bitboard move = board::Knight::southsouthwest(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_southeasteast)
{
    board::Bitboard knight = 1 << 13;
    board::Bitboard move = board::Knight::southeasteast(knight);
    EXPECT_EQ(1 << 7, move);
}

TEST (Knight, southeasteast_out)
{
    board::Bitboard knight = 1ULL << 39;
    board::Bitboard move = board::Knight::southeasteast(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, basic_southwestwest)
{
    board::Bitboard knight = 1 << 29;
    board::Bitboard move = board::Knight::southwestwest(knight);
    EXPECT_EQ(1 << 19, move);
}

TEST (Knight, southwestwest_out)
{
    board::Bitboard knight = 1 << 17;
    board::Bitboard move = board::Knight::southwestwest(knight);
    EXPECT_EQ(0, move);
}

TEST (Knight, generate_moves)
{
    board::Bitboard knight = 1 << 9;
    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight);

    EXPECT_EQ(4, moves.size());

    board::Bitboard expected_moves = 1 << 24 | 1 << 26 | 1 << 3 | 1 << 19;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}

TEST (Knight, generate_moves2)
{
    board::Bitboard knight = 1ULL << 54;
    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight);

    EXPECT_EQ(4, moves.size());

    board::Bitboard expected_moves = 1ULL << 37 | 1ULL << 60 | 1ULL << 39
                                     | 1ULL << 44;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}

TEST (Knight, generate_moves_with_chessboard_none_blocking)
{
    board::Bitboard knight = 1 << 28;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, 1ULL << 63);

    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight, board, board::Color::WHITE);

    EXPECT_EQ(8, moves.size());
}

TEST (Knight, generate_moves_with_chessboard_one_blocking)
{
    board::Bitboard knight = 1 << 9;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, 1 << 24);

    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight, board, board::Color::WHITE);

    EXPECT_EQ(3, moves.size());
}

TEST (Knight, generate_moves_with_chessboard_three_blocking)
{
    board::Bitboard knight = 1ULL << 42;
    board::Chessboard board;
    board::Bitboard blocker = 1Ull << 32 | 1ULL << 52 | 1ULL << 25;
    board.set(board::BitboardType::ALLWHITE, blocker);

    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight, board, board::Color::WHITE);

    EXPECT_EQ(5, moves.size());
}

TEST (Knight, generate_moves_with_chessboard_no_move_possible)
{
    board::Bitboard knight = 1 << 19;
    board::Chessboard board;
    board.set(board::BitboardType::ALLWHITE, board::FullBB);

    std::vector<board::Move> moves;
    board::Knight::generate_moves(moves, knight, board, board::Color::WHITE);

    EXPECT_EQ(0, moves.size());
}
