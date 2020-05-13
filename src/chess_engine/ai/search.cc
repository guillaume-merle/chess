#pragma once

#include <limits>

#include "search.hh"

namespace board
{
    int negaMax(Chessboard board, int depth)
    {
        if (depth == 0)
            return evaluate(board);
        int max = std::numeric_limits<int>::max();
        std::vector<Move> moves = board.generate_legal_moves();
        for ( all moves)
        {
            score = -negaMax(board, depth - 1);
            if(score > max)
                max = score;
        }
        return max;
    }


    Move search(Chessboard board)
    {
        int score = negaMax(board, 1);
        if (!board.white_turn)
            score *= -1;

    }

} // namespace board
