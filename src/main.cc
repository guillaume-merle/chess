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
#include "pgn.hh"

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
        board::pgn(options.pgn_vect_);
    }
    else if (options.perft_)
    {
        board::perft(options.perft_obj_.value());
    }
    else
    {
        ai::init("Chesse James");
    }

    listener::listener_manager.close_listeners();

    return 0;
}
