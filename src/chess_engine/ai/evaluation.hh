#pragma once

#include "chessboard.hh"

namespace board
{
    /**
     * @brief function which evaluate the board, depending the color, the
     * number of pieces and their position on the board.
     */
    int evaluate(Chessboard board);

} // namespace board
