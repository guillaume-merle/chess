#include <limits>

#include "evaluation.hh"
#include "search.hh"

namespace board
{
    /*int negaMax(Chessboard& board, int depth, int color)
    {
        if (depth == 0)
            return evaluate(board) * color;
        int max = std::numeric_limits<int>::min();
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
    }*/

    int negaMax(Chessboard& board, int depth, int color)
    {
        if (depth == 0)
            return evaluate(board);

        int value;

        if (color == 1)
            value = std::numeric_limits<int>::min();
        else
            value = std::numeric_limits<int>::max();

        const std::vector<Move> moves = board.generate_legal_moves();

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = negaMax(new_board, depth - 1, -color);

            if (color == 1)
            {
                if (score > value)
                    value = score;
            }
            else
            {
                if (score < value)
                    value = score;
            }
        }
        return value;
    }

    Move search_move(Chessboard& board)
    {
        int score;
        int depth = 4;
        int value = std::numeric_limits<int>::max();
        std::vector<Move> moves = board.generate_legal_moves();
        Move best_move = moves[0];

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            score = negaMax(new_board, depth - 1, 1);

            if (score < value)
            {
                value = score;
                best_move = move;
            }
        }
        return best_move;
    }
} // namespace board
