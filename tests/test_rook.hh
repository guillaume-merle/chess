#include "gtest/gtest.h"
#include "movegen.hh"

TEST (Rook, generate_moves)
{
    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, 1 << 28);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(14, moves.size());
}

TEST (Rook, generate_moves_northwest)
{
    board::Bitboard rook = 1ULL << 56;

    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(14, moves.size());

    board::Bitboard expected_moves = 0;
    for (board::Bitboard pos = board::south(rook); pos; pos = board::south(pos))
        expected_moves |= pos;
    for (board::Bitboard pos = board::east(rook); pos; pos = board::east(pos))
        expected_moves |= pos;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}

TEST (Rook, generate_moves_southeast)
{
    board::Bitboard rook = 1 << 7;

    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(14, moves.size());

    board::Bitboard expected_moves = 0;
    for (board::Bitboard pos = board::north(rook); pos; pos = board::north(pos))
        expected_moves |= pos;
    for (board::Bitboard pos = board::west(rook); pos; pos = board::west(pos))
        expected_moves |= pos;

    EXPECT_EQ(board::combine_moves(moves), expected_moves);
}

TEST (Rook, generate_moves_with_chessboard_none_blocking)
{
    board::Bitboard rook = 1;

    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);
    board.update_all_boards();
    board.set(board::WHITE, board::ALL, 1 << 9);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(14, moves.size());
}

TEST (Rook, generate_moves_with_chessboard_one_blocking)
{
    board::Bitboard rook = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);
    board.set(board::WHITE, board::ALL, 1 << 3 | rook);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(9, moves.size());
}

TEST (Rook, generate_moves_with_chessboard_no_move_possible)
{
    board::Bitboard rook = 1 << 27;

    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);
    board.update_all_boards();
    board.set(board::WHITE, board::ALL, board::FullBB);

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(0, moves.size());
}

TEST (Rook, generate_moves_with_chessboard_capture)
{
    board::Bitboard rook = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);

    board::Bitboard pawns = 1 << 8;
    board.set(board::BLACK, board::PAWN, pawns);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(8, moves.size());
    EXPECT_EQ(8, moves.at(0).get_to());
    EXPECT_TRUE(moves.at(0).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(0).get_capture());
}

TEST (Rook, generate_moves_with_chessboard_capture_multiple)
{
    board::Bitboard rook = 1;
    board::Chessboard board;
    board.set(board::WHITE, board::ROOK, rook);

    board::Bitboard pawns = 1 << 1 | 1 << 8;
    board.set(board::BLACK, board::PAWN, pawns);
    board.update_all_boards();

    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(2, moves.size());
    for (auto& move : moves)
    {
        EXPECT_TRUE(move.is_capture());
        EXPECT_EQ(board::PieceType::PAWN, move.get_capture());
    }
}
