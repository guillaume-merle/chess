#include <limits>

#include "evaluation.hh"
#include "search.hh"

namespace board
{
    int negaMax(Chessboard& board, int depth, int color)
    {
        if (depth == 0)
            return evaluate(board);
        int max = -10000000;
        const std::vector<Move> moves = board.generate_legal_moves();

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = -negaMax(new_board, depth - 1, -color) * color;

            if (score > max)
                max = score;
        }
        return max;
    }


    Move search_move(Chessboard& board)
    {
        int score;
        int depth = 4;
        int max = -1000000;
        std::vector<Move> moves = board.generate_legal_moves();
        Move best_move = moves[0];

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            score = negaMax(new_board, depth - 1, 1);
            score = 10000000 - score;

            if (score > max)
            {
                max = score;
                best_move = move;
            }
        }
        return best_move;
    }
} // namespace board
