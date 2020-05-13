#include "gtest/gtest.h"

#include "pawn.hh"
#include "bitboard.hh"
#include "movegen.hh"

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

TEST (Pawn, white_promotion)
{
    board::Chessboard board;

    board.set(board::WHITE, board::PAWN, 1ULL << 51);

    board.update_all_boards();

    board::Move move(51, 59, board::PieceType::PAWN, board::PieceType::QUEEN,
                     board::MoveFlag::PROMOTION);

    board.do_move(move, board::Color::WHITE);

    board::Bitboard queen = board.get(board::Color::WHITE,
        board::PieceType::QUEEN);

    EXPECT_EQ(1ULL << 59, queen);
}

TEST (Pawn, generate_white_promotion)
{
    board::Chessboard board;

    board.set(board::WHITE, board::PAWN, 1ULL << 51);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(4, moves.size());

    board.do_move(moves.at(0), board::Color::WHITE);

    board::Bitboard queen = board.get(board::Color::WHITE,
        board::PieceType::QUEEN);

    EXPECT_EQ(1ULL << 59, queen);
}

TEST (Pawn, generate_white_attack_promotion)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 51);
    board.set(board::BLACK, board::PAWN, 1ULL << 58);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(8, moves.size());

    auto move = moves.at(5);

    EXPECT_TRUE(move.is_capture());
    EXPECT_TRUE(move.is_promotion());
    EXPECT_EQ(board::PieceType::KNIGHT, move.get_promotion());

    board.do_move(move, board::Color::WHITE);

    board::Bitboard knight = board.get(board::Color::WHITE,
        board::PieceType::KNIGHT);

    EXPECT_EQ(1ULL << 58, knight);
}

TEST (Pawn, black_promotion)
{
    board::Chessboard board;

    board.set(board::BLACK, board::PAWN, 1ULL << 12);

    board.update_all_boards();

    board::Move move(12, 4, board::PieceType::PAWN, board::PieceType::QUEEN,
                     board::MoveFlag::PROMOTION);

    board.do_move(move, board::Color::BLACK);

    board::Bitboard queen = board.get(board::Color::BLACK,
        board::PieceType::QUEEN);

    EXPECT_EQ(1ULL << 4, queen);
}


TEST (Pawn, generate_white_moves_single)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1 << 16);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(24, moves.at(0).get_to());
}

TEST (Pawn, generate_white_moves_singles_and_double)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1 << 8);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(16, moves.at(0).get_to());
    EXPECT_EQ(24, moves.at(1).get_to());

}

TEST (Pawn, generate_black_moves_singles)
{
    board::Chessboard board;
    board.set(board::BLACK, board::PAWN, 1ULL << 40);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(32, moves.at(0).get_to());
}

TEST (Pawn, generate_black_moves_singles_and_double)
{
    board::Chessboard board;
    board.set(board::BLACK, board::PAWN, 1ULL << 48);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(40, moves.at(0).get_to());
    EXPECT_EQ(32, moves.at(1).get_to());
}

TEST (Pawn, generate_white_moves_out)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 56);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    // for (auto& move : moves)
    // {
        // std::cout << "Move: " << move.get_from() << " to " << move.get_to() << "\n";
    // }

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_black_moves_out)
{
    board::Chessboard board;
    board.set(board::BLACK, board::PAWN, 1);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_moves_with_chessboard_no_move)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 8);
    board.set(board::BLACK, board::PAWN, 1ULL << 16);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_moves_with_chessboard_single_but_not_double)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 8);
    board.set(board::BLACK, board::PAWN, 1ULL << 24);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(1, moves.size());
    EXPECT_EQ(16, moves.at(0).get_to());
}

TEST (Pawn, generate_moves_with_chessboard_no_collision)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 8);
    board.set(board::BLACK, board::PAWN, 1);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(2, moves.size());
    EXPECT_EQ(16, moves.at(0).get_to());
    EXPECT_EQ(24, moves.at(1).get_to());
}

TEST (Pawn, generate_moves_with_chessboard_capture)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 16);
    board.set(board::BLACK, board::PAWN, 1ULL << 25);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(2, moves.size());
    EXPECT_TRUE(moves.at(1).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(1).get_capture());
}

TEST (Pawn, generate_moves_with_chessboard_blocked_by_enemy)
{
    board::Chessboard board;
    board.set(board::BLACK, board::PAWN, 1ULL << 32);
    board.set(board::WHITE, board::PAWN, 1ULL << 24);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board, board::BLACK).get();

    EXPECT_EQ(0, moves.size());
}

TEST (Pawn, generate_moves_with_chessboard_capture_double_push)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 8);
    board.set(board::BLACK, board::PAWN, 1 << 17);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
    EXPECT_TRUE(moves.at(2).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(2).get_capture());
}

TEST (Pawn, generate_moves_with_chessboard_capture_left_and_right)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 17);
    board.set(board::BLACK, board::PAWN, 1ULL << 24 | 1ULL << 26);

    board.update_all_boards();
    std::vector<board::Move> moves = board::MoveGen(board).get();

    EXPECT_EQ(3, moves.size());
    EXPECT_TRUE(moves.at(1).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(1).get_capture());
    EXPECT_TRUE(moves.at(2).is_capture());
    EXPECT_EQ(board::PieceType::PAWN, moves.at(2).get_capture());
}

TEST (Pawn, en_passant_capture)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1 << 13);
    board.set(board::BLACK, board::PAWN, 1 << 28);

    board.update_all_boards();
    auto move =
        board::Move(13, 29, board::PAWN, board::MoveFlag::DOUBLE_PAWN_PUSH);

    board.do_move(move);

    std::vector<board::Move> moves = board.generate_legal_moves();

    EXPECT_EQ(2, moves.size());
    EXPECT_TRUE(moves.at(1).is_en_passant());
}

TEST (Pawn, en_passant_capture_2)
{
    board::Chessboard board;
    board.set(board::WHITE, board::PAWN, 1ULL << 35);
    board.set(board::BLACK, board::PAWN, 1ULL << 50);

    board.update_all_boards();
    auto move =
        board::Move(50, 34, board::PAWN, board::MoveFlag::DOUBLE_PAWN_PUSH);

    board.do_move(move, board::BLACK);

    std::vector<board::Move> moves = board.generate_legal_moves(board::WHITE);

    EXPECT_EQ(2, moves.size());
    EXPECT_TRUE(moves.at(1).is_en_passant());
}

TEST (Pawn, capture_removed_from_board)
{
    board::Chessboard board;
    board.set_turn(board::BLACK);
    board.set(board::WHITE, board::PAWN, 1ULL << 22 | 1ULL << 23);
    board.set(board::BLACK, board::PAWN, 1ULL << 30);

    board.update_all_boards();

    auto move =
        board::Move(30, 23, board::PAWN, board::PAWN, board::MoveFlag::CAPTURE);

    board.do_move(move);

    std::vector<board::Move> moves = board.generate_legal_moves(board::WHITE);

    EXPECT_EQ(1, moves.size());
}
