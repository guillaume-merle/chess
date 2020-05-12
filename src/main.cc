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

int main(int argc, char** argv)
{
    option_parser::parse_options(argc, argv);

    /*board::attacks::init();
    ai::init("Jean-Charles");*/
}
