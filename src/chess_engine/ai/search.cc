#pragma once

#include <limits>

#include "evaluation.hh"
#include "search.hh"

namespace board
{
    int negaMax(Chessboard board, int depth, int color)
    {
        if (depth == 0)
            return evaluate(board) * color;
        int max = std::numeric_limits<int>::max();
        const std::vector<Move> moves = board.generate_legal_moves();
        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            newBoard.do_move(move);

            score = negaMax(new_board, depth - 1, color * -1);

            if (score > max)
                max = score;
        }
        return max;
    }


    Move search(Chessboard board)
    {
        int color;
        int score;
        int depth = 1;
        int max = std::numeric_limits<int>::max();
        const std::vector<Move> moves = board.generate_legal_moves();
        Move best_move;

        if (board.white_turn)
            color = 1;
        else
            color = -1;

       
        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            newBoard.do_move(move);

            score = negaMax(new_board, depth - 1, color);

            if (score > max)
            {
                max = score;
                best_move = move;
            }
        }
        return best_move;
    }
} // namespace board
