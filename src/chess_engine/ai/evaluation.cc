#include "evaluation.hh"

namespace board
{
    int evaluate(Chessboard& board)
    {
        int remaining = popcount(board.get(board.current_color(), ALL));
        return -remaining;
    }

} // namespace board
