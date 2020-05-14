#include <iostream>
#include <dlfcn.h>

#include "chessboard.hh"
#include "pgn-parser.hh"
#include "perft-parser.hh"
#include "option-parser.hh"
#include "listener-manager.hh"
#include "uci.hh"
#include "bitboard.hh"
#include "pawn.hh"
#include "attacks.hh"
#include "perft.hh"
#include "search.hh"

int main(int argc, char** argv)
{
    board::attacks::init();

    option_parser::Options options;
    try {
        options = option_parser::parse_options(argc, argv);
    }
    catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (options.pgn_)
    {
        ; // run with pgn
    }
    else if (options.perft_)
    {
        board::perft(options.perft_obj_.value());
    }
    else
    {
        ai::init("Chesse James \"There can only be one ai in this town\"");
        board::Chessboard board;
        ai::parse_uci_position(ai::get_board(), board);

        board::Move move = board::search_move(board);
        ai::play_move(move.to_string());

        while (!board.is_checkmate(board.current_color()))
        {
            ai::parse_uci_position(ai::get_board(), board);
            board::Move move = board::search_move(board);
            ai::play_move(move.to_string());
        }
    }
}
