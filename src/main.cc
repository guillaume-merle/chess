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

int main(int argc, char** argv)
{
    option_parser::Options options = option_parser::parse_options(argc, argv);

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
        board::attacks::init();
        ai::init("Jean-Charles");
    }
}
