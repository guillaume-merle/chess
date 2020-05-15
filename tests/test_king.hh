#include "gtest/gtest.h"
#include "movegen.hh"

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

TEST (King, white_king_side_castling)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ROOK, 1 << 7);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    // king moves + rook
    EXPECT_EQ(15, moves.size());
    EXPECT_TRUE(moves.at(5).is_king_side_castling());
}

TEST (King, white_queen_side_castling)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ROOK, 1);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    // king moves + rook
    EXPECT_EQ(16, moves.size());
    EXPECT_TRUE(moves.at(5).is_queen_side_castling());
}

TEST (King, black_king_side_castling)
{
    board::Bitboard king = 1ULL << 60;
    board::Chessboard board;

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ROOK, 1ULL << 63);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    // king moves + rook
    EXPECT_EQ(15, moves.size());
    EXPECT_TRUE(moves.at(5).is_king_side_castling());
}

TEST (King, black_queen_side_castling)
{
    board::Bitboard king = 1ULL << 60;
    board::Chessboard board;

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ROOK, 1ULL << 56);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    // king moves + rook
    EXPECT_EQ(16, moves.size());
    EXPECT_TRUE(moves.at(5).is_queen_side_castling());
}

TEST (King, impossible_black_queen_side_castling)
{
    board::Bitboard king = 1ULL << 60;
    board::Chessboard board;

    board.set(board::BLACK, board::KING, king);
    board.set(board::BLACK, board::ROOK, 1ULL << 56);
    board.set(board::WHITE, board::BISHOP, 1ULL << 57);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    // king moves + rook
    EXPECT_EQ(13, moves.size());
    EXPECT_FALSE(moves.at(5).is_queen_side_castling());
}

TEST (King, white_double_castling)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ROOK, 1 | 1 << 7);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    // king moves + rook
    EXPECT_EQ(26, moves.size());
    EXPECT_TRUE(moves.at(5).is_king_side_castling());
    EXPECT_TRUE(moves.at(6).is_queen_side_castling());
}

TEST (King, in_check_impossible_castling)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ROOK, 1 | 1 << 7);
    board.set(board::BLACK, board::QUEEN, 1 << 30);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    // king moves + rook
    for (auto& move : moves)
    {
        EXPECT_FALSE(move.is_queen_side_castling());
        EXPECT_FALSE(move.is_king_side_castling());
    }
}

TEST (King, in_check_one_impossible_castling)
{
    board::Bitboard king = 1 << 4;
    board::Chessboard board;

    board.set(board::WHITE, board::KING, king);
    board.set(board::WHITE, board::ROOK, 1 | 1 << 7);
    board.set(board::BLACK, board::QUEEN, 1ULL << 54);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    int castlings = 0;

    // king moves + rook
    for (auto& move : moves)
    {
        if (move.is_king_side_castling() || move.is_queen_side_castling())
            castlings += 1;
    }

    EXPECT_EQ(1, castlings);
    EXPECT_TRUE(moves.at(5).is_queen_side_castling());
}
