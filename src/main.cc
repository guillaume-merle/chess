#include <iostream>

#include "chessboard.hh"
#include "pgn-parser.hh"
#include "perft-parser.hh"
#include "option-parser.hh"
#include "listener-manager.hh"
#include "uci.hh"
#include "bitboard.hh"
#include "pawn.hh"
#include "attacks.hh"

int main()
{
    board::attacks::init();
    ai::init("Jean-Charles");
}
