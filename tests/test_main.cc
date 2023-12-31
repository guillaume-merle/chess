#include "test_bitboard.hh"
#include "test_pawn.hh"
#include "test_king.hh"
#include "test_knight.hh"
#include "test_bishop.hh"
#include "test_rook.hh"
#include "test_queen.hh"
#include "test_chessboard.hh"
#include "test_attacks.hh"
#include "test_move.hh"
#include "test_move_ordering.hh"
#include "test_zobrist.hh"

#include "move-ordering.hh"
#include "zobrist.hh"

#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ai::MoveOrdering::init();
    board::Zobrist::init();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
