#include <iostream>

#include "chessboard.hh"
#include "pgn-parser.hh"
#include "perft-parser.hh"
#include "option-parser.hh"
#include "listener-manager.hh"
#include "uci.hh"
#include "bitboard.hh"
#include "pawn.hh"
#include "rule.hh"
#include "bishop.hh"
#include "knight.hh"
#include "rook.hh"
#include "queen.hh"
#include "magic.hh"
#include "attacks.hh"

int main()
{
    board::attacks::init();
    // auto chessboard = board::Chessboard();
//
    // chessboard.bitboards_[2] = board::Rank2BB;
//
    // std::cout << "\nMOVES:\n";
    // std::vector<board::Move> moves = generate_pawn_moves(chessboard);
//
    // for (auto& move : moves)
    // {
        // std::cout << "\nFrom:\n";
        // board::print_bitboard(move.get_from());
        // std::cout << "To:\n";
        // board::print_bitboard(move.get_to());
    // }
    //
    std::cout << "BISHOP:\n";

    board::Bitboard bishop = 1ULL << 28;
    std::vector<board::Move> moves;
    moves = board::Bishop::generate_moves(moves, bishop);

    board::Bitboard all_moves = bishop;

    for (auto& move : moves)
    {
        all_moves |= move.get_to();
    }

    board::print_bitboard(all_moves);

    std::cout << "\nROOK:\n";

    board::Bitboard rook = 1ULL << 19;
    moves.clear();
    moves = board::Rook::generate_moves(moves, rook);

    all_moves = rook;
    for (auto& move : moves)
    {
        all_moves |= move.get_to();
    }

    board::print_bitboard(all_moves);

    std::cout << "\nQUEEN:\n";

    board::Bitboard queen = 1ULL << 19;
    moves.clear();
    moves = board::Queen::generate_moves(moves, queen);

    all_moves = queen;
    for (auto& move : moves)
    {
        all_moves |= move.get_to();
    }

    board::print_bitboard(all_moves);

    std::cout << "\nKNIGHT:\n";

    board::Bitboard knight = 1ULL << 19;
    moves.clear();
    moves = board::Knight::generate_moves(moves, knight);

    all_moves = knight;
    for (auto& move : moves)
    {
        all_moves |= move.get_to();
    }

    board::print_bitboard(all_moves);

    board::Bitboard occupancy = 1 << 3 | 1ULL << 32;
    board::Bitboard rook_moves = board::attacks::get_rook_attacks(0, occupancy);

    std::cout << "\n\nRook magic moves:\n";
    board::print_bitboard(rook_moves);

    return 0;
}
