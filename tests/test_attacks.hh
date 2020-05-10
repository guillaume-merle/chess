#include "gtest/gtest.h"

#include "attacks.hh"

TEST (Attacks, knight_attacks)
{
    auto moves = board::attacks::get_knight_attacks(56);

    board::Bitboard expected_moves = 1ULL << 50 | 1ULL << 41;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, knight_attacks2)
{
    auto moves = board::attacks::get_knight_attacks(26);

    board::Bitboard expected_moves = 1 << 16 | 1ULL << 32 | 1ULL << 41
                                     | 1ULL << 43 | 1ULL << 36 | 1 << 20
                                     | 1 << 9 | 1 << 11;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, king_attacks)
{
    auto moves = board::attacks::get_king_attacks(63);

    board::Bitboard expected_moves = 1ULL << 62 | 1ULL << 54 | 1ULL << 55;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, king_attacks2)
{
    auto moves = board::attacks::get_king_attacks(11);

    board::Bitboard expected_moves = 1 << 2 | 1 << 3 | 1 << 4 | 1 << 12
                                     | 1 << 10 | 1 << 18 | 1 << 19 | 1 << 20;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, bishop_attacks)
{
    board::Bitboard occupancy = 1ULL << 36;
    auto moves = board::attacks::get_bishop_attacks(63, occupancy);

    board::Bitboard expected_moves = 1ULL << 54 | 1ULL << 45 | 1ULL << 36;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, bishop_attacks2)
{
    board::Bitboard occupancy = 1ULL << 50 | 1 << 9 | 1 << 29 | 1ULL << 54;
    auto moves = board::attacks::get_bishop_attacks(36, occupancy);

    board::Bitboard expected_moves = 1ULL << 43 | 1ULL << 50 | 1 << 27 | 1 << 18
                                     | 1 << 9 | 1 << 29 | 1ULL << 45
                                     | 1ULL << 54;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, rook_attacks)
{
    board::Bitboard occupancy = 1ULL << 32 | 1ULL << 57;
    auto moves = board::attacks::get_rook_attacks(56, occupancy);

    board::Bitboard expected_moves = 1ULL << 57 | 1ULL << 48 | 1ULL << 40
                                     | 1ULL << 32;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, rook_attacks2)
{
    board::Bitboard occupancy = 1ULL << 37 | 1ULL << 43 | 1 << 11;
    auto moves = board::attacks::get_rook_attacks(35, occupancy);

    board::Bitboard expected_moves = 1ULL << 36 | 1ULL << 37 | 1 << 27
                                     | 1 << 19 | 1 << 11 | 1ULL << 34
                                     | 1ULL << 33 | 1ULL << 32 | 1ULL << 43;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, pawn_right_attacks)
{
    auto moves = board::attacks::get_pawn_attacks(10, board::WHITE);

    board::Bitboard expected_moves = 1 << 19 | 1 << 17;

    EXPECT_EQ(moves, expected_moves);
}

TEST (Attacks, pawn_left_attacks)
{
    auto moves = board::attacks::get_pawn_attacks(58, board::BLACK);

    board::Bitboard expected_moves = 1ULL << 49 | 1ULL << 51;

    EXPECT_EQ(moves, expected_moves);
}
