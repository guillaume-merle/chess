#include "gtest/gtest.h"

#include "zobrist.hh"
#include "chessboard.hh"

using namespace board;

TEST (Zobrist, non_null_key)
{
    Chessboard board(START_POS);
    Zobrist key(board);

    EXPECT_NE(0, key.get());
}

TEST (Zobrist, non_null_key_in_board)
{
    Chessboard board(START_POS);

    EXPECT_NE(0, board.get_zobrist_key().get());
}

TEST (Zobrist, same_board_same_key)
{
    Chessboard board(START_POS);
    Zobrist key(board);
    Zobrist key2(board);

    EXPECT_EQ(key.get(), key2.get());
}

TEST (Zobrist, different_keys)
{
    Chessboard board(START_POS);
    Zobrist key(board);
    Chessboard board2("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");
    Zobrist key2(board2);

    EXPECT_NE(key.get(), key2.get());
}

TEST (Zobrist, switch_turn)
{
    Chessboard board("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 1");
    Zobrist key(board);
    Chessboard board2("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");
    Zobrist key2(board2);

    EXPECT_NE(key.get(), key2.get());
}

TEST (Zobrist, castling_rights)
{
    Chessboard board("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");
    Zobrist key(board);
    Chessboard board2("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQk - 0 1");
    Zobrist key2(board2);

    EXPECT_NE(key.get(), key2.get());
}

TEST (Zobrist, after_move)
{
    Chessboard board(START_POS);
    Zobrist key(board);

    Move move(8, 16, PAWN);
    board.do_move(move);

    Zobrist key2(board);

    EXPECT_NE(key.get(), key2.get());
}
