#pragma once

#include "chessboard.hh"
#include "move.hh"

namespace board
{
    /**
     * @brief function which returns the best move to play.
     */
    Move search_move(Chessboard& board);

} // namespace board
