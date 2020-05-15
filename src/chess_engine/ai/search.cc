#include <limits>

#include "evaluation.hh"
#include "search.hh"

namespace board
{
    int negaMax(Chessboard& board, int depth, int color)
    {
        if (depth == 0)
            return color * evaluate(board);
        int max = std::numeric_limits<int>::max();
        const std::vector<Move> moves = board.generate_legal_moves();

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = -negaMax(new_board, depth - 1, -color);

            if (score > max)
                max = score;
        }
        return max;
    }


    Move search_move(Chessboard& board)
    {
        int score;
        int depth = 4;
        int max = 0;
        std::vector<Move> moves = board.generate_legal_moves();
        Move best_move = moves[0];

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            score = negaMax(new_board, depth - 1, 1);

            if (score > max)
            {
                max = score;
                best_move = move;
            }
        }
        return best_move;
    }
} // namespace board
