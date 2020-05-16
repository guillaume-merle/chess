#pragma once

#include "search.hh"

namespace ai
{
    /**
     * @brief function which evaluate a search, depending the color, the
     * number of pieces and their position on the board.
     *
     * @param search the search to evaluate.
     */
    int evaluate(Chessboard& board);

} // namespace board
