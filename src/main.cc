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

int main()
{
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

    board::Bitboard bishop = 1ULL << 19;
    std::vector<board::Move> moves;
    moves = board::Bishop::generate_moves(moves, bishop);

    board::Bitboard all_moves = bishop;

    for (auto& move : moves)
    {
        all_moves |= move.get_to();
    }

    board::print_bitboard(all_moves);

    return 0;
}
