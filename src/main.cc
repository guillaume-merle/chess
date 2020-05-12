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
#include "rule.hh"
#include "bishop.hh"
#include "knight.hh"
#include "rook.hh"
#include "queen.hh"
#include "magic.hh"
#include "attacks.hh"

int main(int argc, char** argv)
{
    board::attacks::init();
    ai::init("Jean-Charles");
}
