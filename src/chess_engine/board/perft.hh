#pragma once

#include "chessboard.hh"
#include "perft-object.hh"

namespace board
{
    /**
     * @brief compute the perft value for the given PerftObject
     *
     * The perft value corresponds to number of leaves at a certain depth
     * in the tree of legal moves.
     */
    size_t perft(PerftObject& perft_obj);
}
